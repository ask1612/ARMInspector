#include "RpcService.h"
#include "RpcSocket.h"

ParameterInfo::ParameterInfo(const QString &asName, int aType, bool aOut)
    : type(aType),
      jsType(RpcService::convertVariantTypeToJSType(aType)),
      name(asName),
      out(aOut)
{
}

MethodInfo::MethodInfo()
    : returnType(QMetaType::Void),
      valid(false),
      hasOut(false)
{
}

MethodInfo::MethodInfo(const QMetaMethod &aMethod)
    : returnType(QMetaType::Void),
      valid(true),
      hasOut(false)
{
    returnType = aMethod.returnType();
    if (returnType == QMetaType::UnknownType) {
        qJsonRpcDebug() << "RpcService: can't bind method's return type"
                      << QString(aMethod.name());
        valid = false;
        return;
    }

    parameters.reserve(aMethod.parameterCount());

    const QList<QByteArray> &types = aMethod.parameterTypes();
    const QList<QByteArray> &names = aMethod.parameterNames();
    for (int i = 0; i < types.size(); ++i) {
        QByteArray parameterType = types.at(i);
        const QByteArray &parameterName = names.at(i);
        bool out = parameterType.endsWith('&');

        if (out) {
            hasOut = true;
            parameterType.resize(parameterType.size() - 1);
        }

        int type = QMetaType::type(parameterType);
        if (type == 0) {
            qJsonRpcDebug() << "RpcService: can't bind method's parameter"
                          << QString(parameterType);
            valid = false;
            break;
        }

        parameters.append(ParameterInfo(parameterName, type, out));
    }
}

void RpcService::setCurrentRequest(const RpcServiceRequest &aCurrentRequest)
{
    m_currentRequest = aCurrentRequest;
}

const RpcServiceRequest &RpcService::getCurrentRequest() const
{
    return m_currentRequest;
}

RpcService::RpcService(QObject *apParent)
    : QObject(apParent)
{
}

RpcService::~RpcService()
{
}

RpcServiceRequest RpcService::currentRequest() const
{
    return m_currentRequest;
}

void RpcService::beginDelayedResponse()
{
    m_delayedResponse = true;
}

int RpcService::convertVariantTypeToJSType(int aType)
{
    switch (aType) {
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::Double:
    case QMetaType::Long:
    case QMetaType::LongLong:
    case QMetaType::Short:
    case QMetaType::Char:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
    case QMetaType::UShort:
    case QMetaType::UChar:
    case QMetaType::Float:
        return QJsonValue::Double;    // all numeric types in js are doubles
    case QMetaType::QVariantList:
    case QMetaType::QStringList:
        return QJsonValue::Array;
    case QMetaType::QVariantMap:
        return QJsonValue::Object;
    case QMetaType::QString:
        return QJsonValue::String;
    case QMetaType::Bool:
        return QJsonValue::Bool;
    default:
        break;
    }

    return QJsonValue::Undefined;
}

int RpcService::qjsonRpcMessageType = qRegisterMetaType<RpcMessage>("RpcMessage");
void RpcService::cacheInvokableInfo()
{
    const QMetaObject *obj = metaObject();
    int startIdx = staticMetaObject.methodCount(); // skip QObject slots
    for (int idx = startIdx; idx < obj->methodCount(); ++idx) {
        const QMetaMethod method = obj->method(idx);
        if ((method.methodType() == QMetaMethod::Slot &&
             method.access() == QMetaMethod::Public) ||
             method.methodType() == QMetaMethod::Signal) {

            QByteArray signature = method.methodSignature();
            QByteArray methodName = method.name();

            MethodInfo info(method);
            if (!info.valid)
                continue;

            if (signature.contains("QVariant"))
                m_invokableMethodHash[methodName].append(idx);
            else
                m_invokableMethodHash[methodName].prepend(idx);
            m_methodInfoHash[idx] = info;
        }
    }
}

static bool jsParameterCompare(const QJsonArray &parameters,
                               const MethodInfo &info)
{
    int j = 0;
    for (int i = 0; i < info.parameters.size() && j < parameters.size(); ++i) {
        int jsType = info.parameters.at(i).jsType;
        if (jsType != QJsonValue::Undefined && jsType != parameters.at(j).type()) {
            if (!info.parameters.at(i).out)
                return false;
        } else {
            ++j;
        }
    }

    return (j == parameters.size());
}

static  bool jsParameterCompare(const QJsonObject &parameters,
                                const MethodInfo &info)
{
    for (int i = 0; i < info.parameters.size(); ++i) {
        int jsType = info.parameters.at(i).jsType;
        QJsonValue value = parameters.value(info.parameters.at(i).name);
        if (value == QJsonValue::Undefined) {
            if (!info.parameters.at(i).out)
                return false;
        } else if (jsType == QJsonValue::Undefined) {
            continue;
        } else if (jsType != value.type()) {
            return false;
        }
    }

    return true;
}

static inline QVariant convertArgument(const QJsonValue &argument,
                                       const ParameterInfo &info)
{
    if (argument.isUndefined())
        return QVariant(info.type, Q_NULLPTR);

    if (info.type == QMetaType::QJsonValue || info.type == QMetaType::QVariant ||
        info.type >= QMetaType::User) {

        if (info.type == QMetaType::QVariant)
            return argument.toVariant();

        QVariant result(argument);
        if (info.type >= QMetaType::User && result.canConvert(info.type))
            result.convert(info.type);
        return result;
    }

    QVariant result = argument.toVariant();
    if (result.userType() == info.type || info.type == QMetaType::QVariant) {
        return result;
    } else if (result.canConvert(info.type)) {
        result.convert(info.type);
        return result;
    } else if (info.type < QMetaType::User) {
        // already tried for >= user, this is the last resort
        QVariant result(argument);
        if (result.canConvert(info.type)) {
            result.convert(info.type);
            return result;
        }
    }

    return QVariant();
}

QJsonValue RpcService::convertReturnValue(QVariant &aReturnValue)
{
    if (static_cast<int>(aReturnValue.type()) == qMetaTypeId<QJsonObject>())
        return QJsonValue(aReturnValue.toJsonObject());
    else if (static_cast<int>(aReturnValue.type()) == qMetaTypeId<QJsonArray>())
        return QJsonValue(aReturnValue.toJsonArray());

    switch (aReturnValue.type()) {
    case QMetaType::Bool:
    case QMetaType::Int:
    case QMetaType::Double:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
    case QMetaType::UInt:
    case QMetaType::QString:
    case QMetaType::QStringList:
    case QMetaType::QVariantList:
    case QMetaType::QVariantMap:
        return QJsonValue::fromVariant(aReturnValue);
    default:
        // if a conversion operator was registered it will be used
        if (aReturnValue.convert(QMetaType::QJsonValue))
            return aReturnValue.toJsonValue();
        else
            return QJsonValue();
    }
}

static inline QByteArray methodName(const RpcMessage &request)
{
    const QString &methodPath(request.method());
    return methodPath.midRef(methodPath.lastIndexOf('.') + 1).toLatin1();
}

RpcMessage RpcService::dispatch(const RpcMessage &aRequest)
{
    if (aRequest.type() != RpcMessage::Request &&
        aRequest.type() != RpcMessage::Notification) {
        return aRequest.createErrorResponse(ErrorCode::InvalidRequest, "invalid request");
    }

    const QByteArray &method(methodName(aRequest));
    //qDebug() << method;
    if (!m_invokableMethodHash.contains(method)) {
        return aRequest.createErrorResponse(ErrorCode::MethodNotFound, "invalid method called");
    }

    int idx = -1;
    QVariantList arguments;
    const QList<int> &indexes = m_invokableMethodHash.value(method);
    const QJsonValue &params = aRequest.params();
    QVarLengthArray<void *, 10> parameters;
    QVariant returnValue;
    QMetaType::Type returnType = QMetaType::Void;

    bool usingNamedParameters = params.isObject();
    foreach (int methodIndex, indexes) {
        MethodInfo &info = m_methodInfoHash[methodIndex];
        bool methodMatch = usingNamedParameters ?
            jsParameterCompare(params.toObject(), info) :
            jsParameterCompare(params.toArray(), info);

        if (methodMatch) {
            idx = methodIndex;
            arguments.reserve(info.parameters.size());
            returnType = static_cast<QMetaType::Type>(info.returnType);
            returnValue = (returnType == QMetaType::Void) ?
                QVariant() : QVariant(returnType, Q_NULLPTR);
            if (returnType == QMetaType::QVariant)
                parameters.append(&returnValue);
            else
                parameters.append(returnValue.data());

            for (int i = 0; i < info.parameters.size(); ++i) {
                const ParameterInfo &parameterInfo = info.parameters.at(i);
                QJsonValue incomingArgument = usingNamedParameters ?
                    params.toObject().value(parameterInfo.name) :
                    params.toArray().at(i);

                QVariant argument = convertArgument(incomingArgument, parameterInfo);
                if (!argument.isValid()) {
                    QString message = incomingArgument.isUndefined() ?
                        QString("failed to construct default object for '%1'").arg(parameterInfo.name) :
                        QString("failed to convert from JSON for '%1'").arg(parameterInfo.name);
                    return aRequest.createErrorResponse(ErrorCode::InvalidParams, message);
                }

                arguments.push_back(argument);
                if (parameterInfo.type == QMetaType::QVariant)
                    parameters.append(static_cast<void *>(&arguments.last()));
                else
                    parameters.append(const_cast<void *>(arguments.last().constData()));
            }
            break;
        }
    }

    if (idx == -1) {
        return aRequest.createErrorResponse(ErrorCode::InvalidParams, "invalid parameters");
    }

    MethodInfo &info = m_methodInfoHash[idx];

    bool success =
        const_cast<RpcService*>(this)->qt_metacall(QMetaObject::InvokeMetaMethod, idx, parameters.data()) < 0;
    if (!success) {
        QString message = QString("dispatch for method '%1' failed").arg(method.constData());
        return aRequest.createErrorResponse(ErrorCode::InvalidRequest, message);
    }

    if (m_delayedResponse) {
        m_delayedResponse = false;
        return RpcMessage();
    }

    if (info.hasOut) {
        QJsonArray ret;
        if (info.returnType != QMetaType::Void)
            ret.append(convertReturnValue(returnValue));
        for (int i = 0; i < info.parameters.size(); ++i)
            if (info.parameters.at(i).out)
                ret.append(convertReturnValue(arguments[i]));
        if (ret.size() > 1)
            return aRequest.createResponse(ret);
        return aRequest.createResponse(ret.first());
    }

    return aRequest.createResponse(convertReturnValue(returnValue));
}
