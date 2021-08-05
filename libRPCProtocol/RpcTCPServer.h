#ifndef RPCTCPSERVER_H
#define RPCTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

#include "RpcSocket.h"
#include "RpcAbstractServer.h"

class RpcTCPServer : public QTcpServer, public RpcAbstractServer
{
    Q_OBJECT
    Q_DISABLE_COPY(RpcTCPServer)

    QHash<QTcpSocket*, RpcSocket*> m_socketLookup;

protected:
    virtual void incomingConnection(qintptr aSocketDescriptor);

public:
    explicit RpcTCPServer(QObject *apParent = nullptr);
    virtual ~RpcTCPServer();

    virtual bool listen(const QString &asAddress = QString(), quint16 aPort = 0);

    bool addService(RpcService *apService);
    bool removeService(RpcService *apService);

signals:
    void onClientConnected(const RpcSocket* apSocketClient);
    void onClientDisconnected(const RpcSocket* apSocketClient);

protected slots:
    void clientDisconnected();
    void messageProcessing(const RpcMessage &asMessage);

    // RpcAbstractServer interface
public slots:
    void notifyConnectedClients(const RpcMessage &message);
    void notifyConnectedClients(const QString &method, const QJsonArray &params);
};

#endif // RPCTCPSERVER_H
