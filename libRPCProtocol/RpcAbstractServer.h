#ifndef RPCABSTRACTSERVER_H
#define RPCABSTRACTSERVER_H

#include <QList>
#include <QHostAddress>

#include "RpcSocket.h"
#include "RpcMessage.h"
#include "RpcServiceProvider.h"

class RpcAbstractServer : public RpcServiceProvider
{
protected:
    QList<RpcSocket*> m_clients;

public:
    RpcAbstractServer();

    virtual ~RpcAbstractServer();
    virtual int connectedClientCount() const;
    virtual bool listen(const QString &asAddress = QString(), quint16 aPort = 0) = 0;
// signals:
    virtual void onClientConnected(const RpcSocket* apSocketClient) = 0;
    virtual void onClientDisconnected(const RpcSocket* apSocketClient) = 0;

// public slots:
    virtual void notifyConnectedClients(const RpcMessage &message);
    virtual void notifyConnectedClients(const QString &method, const QJsonArray &params);
};

#endif // RPCABSTRACTSERVER_H
