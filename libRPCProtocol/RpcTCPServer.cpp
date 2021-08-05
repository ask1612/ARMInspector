#include "RpcTCPServer.h"

RpcTCPServer::RpcTCPServer(QObject *apParent)
    : QTcpServer(apParent)
{

}

void RpcTCPServer::notifyConnectedClients(const RpcMessage &message)
{
    RpcAbstractServer::notifyConnectedClients(message);
}

void RpcTCPServer::notifyConnectedClients(const QString &method, const QJsonArray &params)
{
    RpcAbstractServer::notifyConnectedClients(method, params);
}

RpcTCPServer::~RpcTCPServer()
{
    foreach (QTcpSocket *socket, m_socketLookup.keys()) {
        socket->flush();
        socket->deleteLater();
    }
    m_socketLookup.clear();

    foreach (RpcSocket *client, m_clients)
        client->deleteLater();
    m_clients.clear();
}

bool RpcTCPServer::listen(const QString &asAddress, quint16 aPort)
{
    return ((asAddress.isNull() || asAddress.isEmpty()) ?
                QTcpServer::listen(QHostAddress::Any, aPort) :
                QTcpServer::listen(QHostAddress(asAddress), aPort));
}

bool RpcTCPServer::addService(RpcService *apService)
{
    if (!RpcServiceProvider::addService(apService))
        return false;

    connect(apService, SIGNAL(notifyConnectedClients(RpcMessage)),
               this, SLOT(notifyConnectedClients(RpcMessage)));
    connect(apService, SIGNAL(notifyConnectedClients(QString,QJsonArray)),
               this, SLOT(notifyConnectedClients(QString,QJsonArray)));
    return true;
}

bool RpcTCPServer::removeService(RpcService *apService)
{
    if (!RpcServiceProvider::removeService(apService))
        return false;

    disconnect(apService, SIGNAL(notifyConnectedClients(RpcMessage)),
                  this, SLOT(notifyConnectedClients(RpcMessage)));
    disconnect(apService, SIGNAL(notifyConnectedClients(QString,QJsonArray)),
                  this, SLOT(notifyConnectedClients(QString,QJsonArray)));
    return true;
}

void RpcTCPServer::clientDisconnected()
{
    QTcpSocket *tcpSocket = static_cast<QTcpSocket*>(sender());
    if (!tcpSocket) {
        qJsonRpcDebug() << "called with invalid socket";
        return;
    }

    RpcSocket *socket {nullptr};
    if (m_socketLookup.contains(tcpSocket)) {
        socket = m_socketLookup.take(tcpSocket);
        m_clients.removeAll(socket);
        socket->deleteLater();
    }

    tcpSocket->deleteLater();
    emit onClientDisconnected(socket);
}

void RpcTCPServer::messageProcessing(const RpcMessage &asMessage)
{
    RpcSocket *socket = static_cast<RpcSocket*>(sender());
    if (!socket) {
        qJsonRpcDebug() << "called without service socket";
        return;
    }

    processMessage(socket, asMessage);
}

void RpcTCPServer::incomingConnection(qintptr aSocketDescriptor)
{
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    if (!tcpSocket->setSocketDescriptor(aSocketDescriptor))
    {
        qJsonRpcDebug() << "can't set socket descriptor";
        tcpSocket->deleteLater();
        return;
    }

    QIODevice *device = qobject_cast<QIODevice*>(tcpSocket);
    RpcSocket *socket = new RpcSocket(device, this);
    connect(socket, SIGNAL(messageReceived(RpcMessage)),
              this, SLOT(messageProcessing(RpcMessage)));
    m_clients.append(socket);
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    m_socketLookup.insert(tcpSocket, socket);
    emit onClientConnected(socket);
}
