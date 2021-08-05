#include "RpcMessage.h"

class RpcMessagePrivate : public QSharedData
{
public:
    RpcMessagePrivate();
    ~RpcMessagePrivate();
    RpcMessagePrivate(const RpcMessagePrivate &aRpcMessagePrivate);

    void initializeWithObject(const QJsonObject &aMessage);
    static RpcMessage createBasicRequest(const QString &asMethod, const QJsonArray &aParams);
    static RpcMessage createBasicRequest(const QString &asMethod,
                                              const QJsonObject &aNamedParameters);

    RpcMessage::Type m_type;
    QScopedPointer<QJsonObject> m_pObject;

    static int uniqueRequestCounter;
};

int RpcMessagePrivate::uniqueRequestCounter = 0;

RpcMessagePrivate::RpcMessagePrivate()
    : m_type(RpcMessage::Invalid),
      m_pObject(nullptr)
{
}

RpcMessagePrivate::RpcMessagePrivate(const RpcMessagePrivate &aRpcMessagePrivate)
    : QSharedData(aRpcMessagePrivate),
      m_type(aRpcMessagePrivate.m_type),
      m_pObject(aRpcMessagePrivate.m_pObject ? new QJsonObject(*aRpcMessagePrivate.m_pObject) : nullptr)
{
}

void RpcMessagePrivate::initializeWithObject(const QJsonObject &aMessage)
{
    m_pObject.reset(new QJsonObject(aMessage));
    if (aMessage.contains(QLatin1String("id"))) {
        if (aMessage.contains(QLatin1String("result")) ||
            aMessage.contains(QLatin1String("error"))) {
            if (aMessage.contains(QLatin1String("error")) &&
                !aMessage.value(QLatin1String("error")).isNull())
                m_type = RpcMessage::Error;
            else
                m_type = RpcMessage::Response;
        } else if (aMessage.contains(QLatin1String("method"))) {
            m_type = RpcMessage::Request;
        }
    } else {
        if (aMessage.contains(QLatin1String("method")))
            m_type = RpcMessage::Notification;
    }
}

RpcMessagePrivate::~RpcMessagePrivate()
{
}

RpcMessage::RpcMessage()
    : d(new RpcMessagePrivate)
{
    d->m_pObject.reset(new QJsonObject);
}

RpcMessage::RpcMessage(const RpcMessage &aRPCMessage)
    : d(aRPCMessage.d)
{
}

RpcMessage::~RpcMessage()
{
}

RpcMessage &RpcMessage::operator=(const RpcMessage &aRPCMessage)
{
    d = aRPCMessage.d;
    return *this;
}

bool RpcMessage::operator==(const RpcMessage &aRpcMessage) const
{
    if (aRpcMessage.d == d)
        return true;

    if (aRpcMessage.type() == type()) {
        if (aRpcMessage.type() == RpcMessage::Error) {
            return (aRpcMessage.errorCode() == errorCode() &&
                    aRpcMessage.errorMessage() == errorMessage() &&
                    aRpcMessage.errorData() == errorData());
        } else {
            if (aRpcMessage.type() == RpcMessage::Notification) {
                return (aRpcMessage.method() == method() &&
                        aRpcMessage.params() == params());
            } else {
                return (aRpcMessage.id() == id() &&
                        aRpcMessage.method() == method() &&
                        aRpcMessage.params() == params());
            }
        }
    }

    return false;
}

RpcMessage RpcMessage::fromJson(const QByteArray &aData)
{
    RpcMessage result;
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(aData, &error);
    if (error.error != QJsonParseError::NoError) {
        qJsonRpcDebug() << error.errorString();
        return result;
    }

    if (!document.isObject()) {
        qJsonRpcDebug() << "invalid message: " << aData;
        return result;
    }

    result.d->initializeWithObject(document.object());
    return result;
}

RpcMessage RpcMessage::fromObject(const QJsonObject &aObject)
{
    RpcMessage result;
    result.d->initializeWithObject(aObject);
    return result;
}

QJsonObject RpcMessage::toObject() const
{
    if (d->m_pObject)
        return QJsonObject(*d->m_pObject);
    return QJsonObject();
}

QByteArray RpcMessage::toJson() const
{
    if (d->m_pObject) {
        QJsonDocument doc(*d->m_pObject);
        return doc.toJson();
    }

    return QByteArray();
}

bool RpcMessage::isValid() const
{
    return d->m_type != RpcMessage::Invalid;
}

RpcMessage::Type RpcMessage::type() const
{
    return d->m_type;
}

RpcMessage RpcMessagePrivate::createBasicRequest(const QString &asMethod, const QJsonArray &aParams)
{
    RpcMessage request;
    request.d->m_pObject->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
    request.d->m_pObject->insert(QLatin1String("method"), asMethod);
    if (!aParams.isEmpty())
        request.d->m_pObject->insert(QLatin1String("params"), aParams);
    return request;
}

RpcMessage RpcMessagePrivate::createBasicRequest(const QString &asMethod,
                                                           const QJsonObject &aNamedParameters)
{
    RpcMessage request;
    request.d->m_pObject->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
    request.d->m_pObject->insert(QLatin1String("method"), asMethod);
    if (!aNamedParameters.isEmpty())
        request.d->m_pObject->insert(QLatin1String("params"), aNamedParameters);
    return request;
}

RpcMessage RpcMessage::createRequest(const QString &asMethod, const QJsonArray &aParams)
{
    RpcMessage request = RpcMessagePrivate::createBasicRequest(asMethod, aParams);
    request.d->m_type = RpcMessage::Request;
    RpcMessagePrivate::uniqueRequestCounter++;
    request.d->m_pObject->insert(QLatin1String("id"), RpcMessagePrivate::uniqueRequestCounter);
    return request;
}

RpcMessage RpcMessage::createRequest(const QString &asMethod, const QJsonValue &aParam)
{
    QJsonArray params;
    params.append(aParam);
    return createRequest(asMethod, params);
}

RpcMessage RpcMessage::createRequest(const QString &asMethod,
                                               const QJsonObject &aNamedParameters)
{
    RpcMessage request =
        RpcMessagePrivate::createBasicRequest(asMethod, aNamedParameters);
    request.d->m_type = RpcMessage::Request;
    RpcMessagePrivate::uniqueRequestCounter++;
    request.d->m_pObject->insert(QLatin1String("id"), RpcMessagePrivate::uniqueRequestCounter);
    return request;
}

RpcMessage RpcMessage::createNotification(const QString &asMethod, const QJsonArray &aParams)
{
    RpcMessage notification = RpcMessagePrivate::createBasicRequest(asMethod, aParams);
    notification.d->m_type = RpcMessage::Notification;
    return notification;
}

RpcMessage RpcMessage::createNotification(const QString &asMethod, const QJsonValue &aParam)
{
    QJsonArray params;
    params.append(aParam);
    return createNotification(asMethod, params);
}

RpcMessage RpcMessage::createNotification(const QString &asMethod,
                                                    const QJsonObject &aNamedParameters)
{
    RpcMessage notification =
        RpcMessagePrivate::createBasicRequest(asMethod, aNamedParameters);
    notification.d->m_type = RpcMessage::Notification;
    return notification;
}

RpcMessage RpcMessage::createResponse(const QJsonValue &aResult) const
{
    RpcMessage response;
    if (d->m_pObject->contains(QLatin1String("id"))) {
        QJsonObject *object = response.d->m_pObject.data();
        object->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
        object->insert(QLatin1String("id"), d->m_pObject->value(QLatin1String("id")));
        object->insert(QLatin1String("result"), aResult);
        response.d->m_type = RpcMessage::Response;
    }

    return response;
}

RpcMessage RpcMessage::createErrorResponse(ErrorCode aCode,
                                                     const QString &asMessage,
                                                     const QJsonValue &aData) const
{
    RpcMessage response;
    QJsonObject error;
    error.insert(QLatin1String("code"), aCode);
    if (!asMessage.isEmpty())
        error.insert(QLatin1String("message"), asMessage);
    if (!aData.isUndefined())
        error.insert(QLatin1String("data"), aData);

    response.d->m_type = RpcMessage::Error;
    QJsonObject *object = response.d->m_pObject.data();
    object->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
    if (d->m_pObject->contains(QLatin1String("id")))
        object->insert(QLatin1String("id"), d->m_pObject->value(QLatin1String("id")));
    else
        object->insert(QLatin1String("id"), 0);
    object->insert(QLatin1String("error"), error);
    return response;
}

int RpcMessage::id() const
{
    if (d->m_type == RpcMessage::Notification || !d->m_pObject)
        return -1;

    const QJsonValue &value = d->m_pObject->value(QLatin1String("id"));
    if (value.isString())
        return value.toString().toInt();
    return value.toInt();
}

QString RpcMessage::method() const
{
    if (d->m_type == RpcMessage::Response || !d->m_pObject)
        return QString();

    return d->m_pObject->value(QLatin1String("method")).toString();
}

QJsonValue RpcMessage::params() const
{
    if (d->m_type == RpcMessage::Response || d->m_type == RpcMessage::Error)
        return QJsonValue(QJsonValue::Undefined);
    if (!d->m_pObject)
        return QJsonValue(QJsonValue::Undefined);

    return d->m_pObject->value(QLatin1String("params"));
}

QJsonValue RpcMessage::result() const
{
    if (d->m_type != RpcMessage::Response || !d->m_pObject)
        return QJsonValue(QJsonValue::Undefined);

    return d->m_pObject->value(QLatin1String("result"));
}

int RpcMessage::errorCode() const
{
    if (d->m_type != RpcMessage::Error || !d->m_pObject)
        return 0;

    QJsonObject error =
        d->m_pObject->value(QLatin1String("error")).toObject();
    const QJsonValue &value = error.value(QLatin1String("code"));
    if (value.isString())
        return value.toString().toInt();
    return value.toInt();
}

QString RpcMessage::errorMessage() const
{
    if (d->m_type != RpcMessage::Error || !d->m_pObject)
        return QString();

    QJsonObject error =
        d->m_pObject->value(QLatin1String("error")).toObject();
    return error.value(QLatin1String("message")).toString();
}

QJsonValue RpcMessage::errorData() const
{
    if (d->m_type != RpcMessage::Error || !d->m_pObject)
        return QJsonValue(QJsonValue::Undefined);

    QJsonObject error =
        d->m_pObject->value(QLatin1String("error")).toObject();
    return error.value(QLatin1String("data"));
}

static QDebug operator<<(QDebug dbg, RpcMessage::Type type)
{
    switch (type) {
    case RpcMessage::Request:
        return dbg << "RpcMessage::Request";
    case RpcMessage::Response:
        return dbg << "RpcMessage::Response";
    case RpcMessage::Notification:
        return dbg << "RpcMessage::Notification";
    case RpcMessage::Error:
        return dbg << "RpcMessage::Error";
    default:
        return dbg << "RpcMessage::Invalid";
    }
}

QDebug operator<<(QDebug dbg, const RpcMessage &msg)
{
    dbg.nospace() << "RpcMessage(type=" << msg.type();
    if (msg.type() != RpcMessage::Notification) {
        dbg.nospace() << ", id=" << msg.id();
    }

    if (msg.type() == RpcMessage::Request ||
        msg.type() == RpcMessage::Notification) {
        dbg.nospace() << ", method=" << msg.method()
                      << ", params=" << msg.params();
    } else if (msg.type() == RpcMessage::Response) {
        dbg.nospace() << ", result=" << msg.result();
    } else if (msg.type() == RpcMessage::Error) {
        dbg.nospace() << ", code=" << msg.errorCode()
                      << ", message=" << msg.errorMessage()
                      << ", data=" << msg.errorData();
    }
    dbg.nospace() << ")";
    return dbg.space();
}
