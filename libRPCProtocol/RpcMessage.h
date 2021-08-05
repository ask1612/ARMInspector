#ifndef RPCMESSAGE_H
#define RPCMESSAGE_H

#include <QSharedDataPointer>
#include <QMetaType>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#define qJsonRpcDebug if (qgetenv("QJSONRPC_DEBUG").isEmpty()); else qDebug

enum ErrorCode {
    NoError         = 0,
    ParseError      = -32700,           // Invalid JSON was received by the server.
                                        // An error occurred on the server while parsing the JSON text.
    InvalidRequest  = -32600,           // The JSON sent is not a valid Request object.
    MethodNotFound  = -32601,           // The method does not exist / is not available.
    InvalidParams   = -32602,           // Invalid method parameter(s).
    InternalError   = -32603,           // Internal JSON-RPC error.
    ServerErrorBase = -32000,           // Reserved for implementation-defined server-errors.
    UserError       = -32099,           // Anything after this is user defined
    TimeoutError    = -32100
};
Q_DECLARE_METATYPE(ErrorCode)

class RpcMessagePrivate;
class RpcMessage
{
    friend class RpcMessagePrivate;
    QSharedDataPointer<RpcMessagePrivate> d;

public:
    RpcMessage();
    RpcMessage(const RpcMessage &aRPCMessage);
    RpcMessage &operator=(const RpcMessage &aRPCMessage);
    ~RpcMessage();

    inline void swap(RpcMessage &aRPCMessage) { qSwap(d, aRPCMessage.d); }

    enum Type {
        Invalid,
        Request,
        Response,
        Notification,
        Error
    };

    static RpcMessage createRequest(const QString &asMethod,
                                         const QJsonArray &aParams = QJsonArray());
    static RpcMessage createRequest(const QString &asMethod, const QJsonValue &aParam);
    static RpcMessage createRequest(const QString &asMethod, const QJsonObject &aNamedParameters);

    static RpcMessage createNotification(const QString &asMethod,
                                              const QJsonArray &aParams = QJsonArray());
    static RpcMessage createNotification(const QString &asMethod, const QJsonValue &aParam);
    static RpcMessage createNotification(const QString &asMethod,
                                              const QJsonObject &aNamedParameters);

    RpcMessage createResponse(const QJsonValue &aResult) const;
    RpcMessage createErrorResponse(ErrorCode aCode,
                                        const QString &asMessage = QString(),
                                        const QJsonValue &aData = QJsonValue()) const;

    RpcMessage::Type type() const;
    bool isValid() const;
    int id() const;

    // request
    QString method() const;
    QJsonValue params() const;

    // response
    QJsonValue result() const;

    // error
    int errorCode() const;
    QString errorMessage() const;
    QJsonValue errorData() const;

    QJsonObject toObject() const;
    static RpcMessage fromObject(const QJsonObject &aObject);

    QByteArray toJson() const;
    static RpcMessage fromJson(const QByteArray &aData);

    bool operator==(const RpcMessage &aRpcMessage) const;
    inline bool operator!=(const RpcMessage &aRpcMessage) const { return !(operator==(aRpcMessage)); }
};

QDebug operator<<(QDebug, const RpcMessage &);
Q_DECLARE_METATYPE(RpcMessage)
Q_DECLARE_SHARED(RpcMessage)

#endif // RPCMESSAGE_H
