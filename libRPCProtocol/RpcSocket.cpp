#include "RpcSocket.h"
#include "RpcService.h"

RpcSocket::RpcSocket(QObject *apParent)
    : QObject(apParent)
{

}

RpcSocket::RpcSocket(QIODevice *apDevice, QObject *apParent)
    : QObject(apParent)
{
    m_pDevice = apDevice;
    connect(m_pDevice, SIGNAL(readyRead()), this, SLOT(processIncomingData()));
}

RpcSocket::~RpcSocket()
{
}

int RpcSocket::findJsonDocumentEnd(const QByteArray &aJsonData)
{
    const char* pos = aJsonData.constData();
    const char* end = pos + aJsonData.length();

    char blockStart = 0;
    char blockEnd = 0;
    int index = 0;

    while (true) {
        if (pos == end) {
            return -1;
        } else if (*pos == '{') {
            blockStart = '{';
            blockEnd = '}';
            break;
        } else if(*pos == '[') {
            blockStart = '[';
            blockEnd = ']';
            break;
        }

        pos++;
        index++;
    }

    pos++;
    index++;
    int depth = 1;
    bool inString = false;
    while (depth > 0 && pos <= end) {
        if (*pos == '\\') {
            pos += 2;
            index += 2;
            continue;
        } else if (*pos == '"') {
            inString = !inString;
        } else if (!inString) {
            if (*pos == blockStart)
                depth++;
            else if (*pos == blockEnd)
                depth--;
        }

        pos++;
        index++;
    }

    return depth == 0 ? index-1 : -1;
}

void RpcSocket::writeData(const RpcMessage &asMessage)
{
    QJsonDocument doc = QJsonDocument(asMessage.toObject());
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    m_pDevice.data()->write(data);
    qJsonRpcDebug() << "sending: " << data;
}

void RpcSocket::setDefaultRequestTimeout(int aiMsecs)
{
    if (aiMsecs < 0) {
        qJsonRpcDebug() << "Cannot set a negative request timeout msecs value";
        return;
    }

    m_defaultRequestTimeout = aiMsecs;
}

int RpcSocket::getDefaultRequestTimeout() const
{
    return m_defaultRequestTimeout;
}

bool RpcSocket::isValid() const
{
    return m_pDevice && m_pDevice.data()->isOpen();
}

RpcMessage RpcSocket::sendMessageBlocking(const RpcMessage &asMessage, int aMsecs)
{
    RpcServiceReply *reply = sendMessage(asMessage);
    QScopedPointer<RpcServiceReply> replyPtr(reply);

    QEventLoop responseLoop;
    connect(reply, SIGNAL(finished()), &responseLoop, SLOT(quit()));
    QTimer::singleShot(aMsecs, &responseLoop, SLOT(quit()));
    responseLoop.exec();

    if (!reply->response().isValid()) {
        m_replies.remove(asMessage.id());
        return asMessage.createErrorResponse(ErrorCode::TimeoutError, "request timed out");
    }

    return reply->response();
}

RpcServiceReply *RpcSocket::sendMessage(const RpcMessage &asMessage)
{
    if (!m_pDevice) {
        qJsonRpcDebug() << "trying to send message without device";
        return nullptr;
    }

    notify(asMessage);
    QPointer<RpcServiceReply> reply(new RpcServiceReply);
    reply->setRequest(asMessage);
    m_replies.insert(asMessage.id(), reply);
    return reply;
}

void RpcSocket::notify(const RpcMessage &asMessage)
{
    if (!m_pDevice) {
        qJsonRpcDebug() << "trying to send message without device";
        return;
    }

    RpcService *service = qobject_cast<RpcService*>(sender());
    if (service)
        disconnect(service, SIGNAL(result(RpcMessage)), this, SLOT(notify(RpcMessage)));

    writeData(asMessage);
}

RpcMessage RpcSocket::invokeRemoteMethodBlocking(const QString &asMethod, int aMsecs, const QVariant &param1,
                                                           const QVariant &param2, const QVariant &param3,
                                                           const QVariant &param4, const QVariant &param5,
                                                           const QVariant &param6, const QVariant &param7,
                                                           const QVariant &param8, const QVariant &param9,
                                                           const QVariant &param10)
{
    QVariantList params;
    if (param1.isValid()) params.append(param1);
    if (param2.isValid()) params.append(param2);
    if (param3.isValid()) params.append(param3);
    if (param4.isValid()) params.append(param4);
    if (param5.isValid()) params.append(param5);
    if (param6.isValid()) params.append(param6);
    if (param7.isValid()) params.append(param7);
    if (param8.isValid()) params.append(param8);
    if (param9.isValid()) params.append(param9);
    if (param10.isValid()) params.append(param10);

    RpcMessage request =
        RpcMessage::createRequest(asMethod, QJsonArray::fromVariantList(params));
    return sendMessageBlocking(request, aMsecs);
}

RpcMessage RpcSocket::invokeRemoteMethodBlocking(const QString &asMethod, const QVariant &param1,
                                                           const QVariant &param2, const QVariant &param3,
                                                           const QVariant &param4, const QVariant &param5,
                                                           const QVariant &param6, const QVariant &param7,
                                                           const QVariant &param8, const QVariant &param9,
                                                           const QVariant &param10)
{
    return invokeRemoteMethodBlocking(asMethod, m_defaultRequestTimeout, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10);
}

RpcServiceReply *RpcSocket::invokeRemoteMethod(const QString &asMethod, const QVariant &param1,
                                                         const QVariant &param2, const QVariant &param3,
                                                         const QVariant &param4, const QVariant &param5,
                                                         const QVariant &param6, const QVariant &param7,
                                                         const QVariant &param8, const QVariant &param9,
                                                         const QVariant &param10)
{
    QVariantList params;
    if (param1.isValid()) params.append(param1);
    if (param2.isValid()) params.append(param2);
    if (param3.isValid()) params.append(param3);
    if (param4.isValid()) params.append(param4);
    if (param5.isValid()) params.append(param5);
    if (param6.isValid()) params.append(param6);
    if (param7.isValid()) params.append(param7);
    if (param8.isValid()) params.append(param8);
    if (param9.isValid()) params.append(param9);
    if (param10.isValid()) params.append(param10);

    RpcMessage request =
        RpcMessage::createRequest(asMethod, QJsonArray::fromVariantList(params));
    return sendMessage(request);
}

void RpcSocket::processIncomingData()
{
    if (!m_pDevice) {
        qJsonRpcDebug() << "called without device";
        return;
    }

    m_aBuffer.append(m_pDevice.data()->readAll());
    while (!m_aBuffer.isEmpty()) {
        int dataSize = findJsonDocumentEnd(m_aBuffer);
        if (dataSize == -1) {
            return;
        }

        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(m_aBuffer.mid(0, dataSize + 1), &error);
        if (document.isEmpty()) {
            if (error.error != QJsonParseError::NoError) {
                qJsonRpcDebug() << error.errorString();
            }

            break;
        }

        m_aBuffer = m_aBuffer.mid(dataSize + 1);
        if (document.isArray()) {
            qJsonRpcDebug() << "bulk support is current disabled";
        } else if (document.isObject()){
            qJsonRpcDebug() << "received: " << document.toJson(QJsonDocument::Compact);
            RpcMessage message = RpcMessage::fromObject(document.object());
            Q_EMIT messageReceived(message);

            if (message.type() == RpcMessage::Response ||
                message.type() == RpcMessage::Error) {
                if (m_replies.contains(message.id())) {
                    QPointer<RpcServiceReply> reply = m_replies.take(message.id());
                    if (!reply.isNull()) {
                        reply->setResponse(message);
                        reply->finished();
                    }
                }
            } else {
                processRequestMessage(message);
            }
        }
    }
}

void RpcSocket::setIODevice(QIODevice *pDevice)
{
    m_pDevice = pDevice;
    connect(m_pDevice, SIGNAL(readyRead()), this, SLOT(processIncomingData()));
}

void RpcSocket::processRequestMessage(const RpcMessage &asMessage)
{
    Q_UNUSED(asMessage)
}
