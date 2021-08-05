#include "RpcLocalServer.h"

RpcLocalServer::RpcLocalServer(QObject *apParent)
    : QLocalServer(apParent)
{
    this->setSocketOptions(QLocalServer::WorldAccessOption);
}

RpcLocalServer::~RpcLocalServer()
{
    foreach (QLocalSocket *socket, m_socketLookup.keys()) {
        socket->flush();
        socket->deleteLater();
    }
    m_socketLookup.clear();

    foreach (RpcSocket *client, m_clients)
        client->deleteLater();
    m_clients.clear();
}

bool RpcLocalServer::listen(const QString &asAddress, quint16 aPort)
{
    Q_UNUSED(aPort);

    return QLocalServer::listen(asAddress);
}

bool RpcLocalServer::addService(RpcService *apService)
{
    if (!RpcServiceProvider::addService(apService))
        return false;

    connect(apService, SIGNAL(notifyConnectedClients(RpcMessage)),
               this, SLOT(notifyConnectedClients(RpcMessage)));
    connect(apService, SIGNAL(notifyConnectedClients(QString,QJsonArray)),
               this, SLOT(notifyConnectedClients(QString,QJsonArray)));
    return true;
}

bool RpcLocalServer::removeService(RpcService *apService)
{
    if (!RpcServiceProvider::removeService(apService))
        return false;

    disconnect(apService, SIGNAL(notifyConnectedClients(RpcMessage)),
                  this, SLOT(notifyConnectedClients(RpcMessage)));
    disconnect(apService, SIGNAL(notifyConnectedClients(QString,QJsonArray)),
                  this, SLOT(notifyConnectedClients(QString,QJsonArray)));
    return true;
}

void RpcLocalServer::clientDisconnected()
{
    QLocalSocket *localSocket = static_cast<QLocalSocket*>(sender());
    if (!localSocket) {
        qJsonRpcDebug() << "called with invalid socket";
        return;
    }
    if (m_socketLookup.contains(localSocket)) {
        RpcSocket *socket = m_socketLookup.take(localSocket);
        m_clients.removeAll(socket);
        socket->deleteLater();
    }

    localSocket->deleteLater();
    emit onClientDisconnected();
}

void RpcLocalServer::messageProcessing(const RpcMessage &asMessage)
{
    RpcSocket *socket = static_cast<RpcSocket*>(sender());
    if (!socket) {
        qJsonRpcDebug() << "called without service socket";
        return;
    }

    processMessage(socket, asMessage);
}

void RpcLocalServer::notifyConnectedClients(const RpcMessage &message)
{
    RpcAbstractServer::notifyConnectedClients(message);
}

void RpcLocalServer::notifyConnectedClients(const QString &method, const QJsonArray &params)
{
    RpcAbstractServer::notifyConnectedClients(method, params);
}

void RpcLocalServer::incomingConnection(quintptr aSocketDescriptor)
{
    QLocalSocket *localSocket = new QLocalSocket(this);
    if (!localSocket->setSocketDescriptor(aSocketDescriptor)) {
        qJsonRpcDebug() << "nextPendingConnection is null";
        localSocket->deleteLater();
        return;
    }

    QIODevice *device = qobject_cast<QIODevice*>(localSocket);
    RpcSocket *socket = new RpcSocket(device, this);
    connect(socket, SIGNAL(messageReceived(RpcMessage)),
              this, SLOT(messageProcessing(RpcMessage)));
    m_clients.append(socket);
    connect(localSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    m_socketLookup.insert(localSocket, socket);
    emit onClientConnected();
}
