#ifndef RPCSERVICE_H
#define RPCSERVICE_H

#include <QObject>
#include <QVariant>
#include <QPointer>
#include <QVarLengthArray>
#include <QMetaMethod>
#include <QEventLoop>
#include <QDebug>


#include "RpcMessage.h"
#include "RpcServiceRequest.h"

struct ParameterInfo
{
    ParameterInfo(const QString &asName = QString(), int aType = 0, bool aOut = false);

    int type;
    int jsType;
    QString name;
    bool out;
};

struct MethodInfo
{
    MethodInfo();
    MethodInfo(const QMetaMethod &aMethod);

    QVarLengthArray<ParameterInfo> parameters;
    int returnType;
    bool valid;
    bool hasOut;
};

class RpcService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RpcService)

    QHash<int, MethodInfo > m_methodInfoHash;
    QHash<QByteArray, QList<int> > m_invokableMethodHash;
    RpcServiceRequest m_currentRequest;
    bool m_delayedResponse {false};

protected:
    RpcServiceRequest currentRequest() const;
    void beginDelayedResponse();

public:
    explicit RpcService(QObject *apParent = nullptr);
    ~RpcService();

    void cacheInvokableInfo();
    static int qjsonRpcMessageType;
    static int convertVariantTypeToJSType(int aType);
    static QJsonValue convertReturnValue(QVariant &aReturnValue);

    void setCurrentRequest(const RpcServiceRequest &aCurrentRequest);
    const RpcServiceRequest& getCurrentRequest() const;

signals:
    void result(const RpcMessage &aRpcMessage);
    void notifyConnectedClients(const RpcMessage &aRpcMessage);
    void notifyConnectedClients(const QString &asMethod, const QJsonArray &aParams = QJsonArray());

public slots:
    RpcMessage dispatch(const RpcMessage &aRequest);
};

#endif // RPCSERVICE_H

