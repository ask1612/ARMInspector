#include "RpcAbstractServer.h"

RpcAbstractServer::RpcAbstractServer()
{

}

RpcAbstractServer::~RpcAbstractServer()
{

}

int RpcAbstractServer::connectedClientCount() const
{
    return m_clients.size();
}

void RpcAbstractServer::notifyConnectedClients(const RpcMessage &message)
{
    for (int i = 0; i < m_clients.size(); ++i)
        m_clients[i]->sendMessage(message);
}

void RpcAbstractServer::notifyConnectedClients(const QString &method, const QJsonArray &params)
{
    RpcMessage notification =
        RpcMessage::createNotification(method, params);
    notifyConnectedClients(notification);
}
