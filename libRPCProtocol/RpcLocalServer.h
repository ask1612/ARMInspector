#ifndef RPCLOCALSERVER_H
#define RPCLOCALSERVER_H

#include <QObject>
#include <QLocalSocket>
#include <QLocalServer>

#include "RpcSocket.h"
#include "RpcService.h"
#include "RpcAbstractServer.h"

class RpcLocalServer : public QLocalServer, public RpcAbstractServer
{
    Q_OBJECT
    Q_DISABLE_COPY(RpcLocalServer)

    QHash<QLocalSocket*, RpcSocket*> m_socketLookup;

protected:
    virtual void incomingConnection(quintptr aSocketDescriptor);

public:
    explicit RpcLocalServer(QObject *apParent = nullptr);
    virtual ~RpcLocalServer();

    virtual bool listen(const QString &asAddress = QString(), quint16 aPort = 0);
    bool addService(RpcService *apService);
    bool removeService(RpcService *apService);

signals:
    void onClientConnected();
    void onClientDisconnected();

private slots:
    void clientDisconnected();
    void messageProcessing(const RpcMessage &asMessage);

    // RpcAbstractServer interface
public slots:
    void notifyConnectedClients(const RpcMessage &message);
    void notifyConnectedClients(const QString &method, const QJsonArray &params);
};

#endif // RPCLOCALSERVER_H
