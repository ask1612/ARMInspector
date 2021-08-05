#ifndef RPCSERVICEPROVIDER_H
#define RPCSERVICEPROVIDER_H

#include <QScopedPointer>
#include <QObjectCleanupHandler>
#include <QHash>
#include <QMetaObject>
#include <QMetaClassInfo>
#include <QDebug>

#include "RpcService.h"

class RpcServiceProvider
{
    QHash<QByteArray, RpcService*> m_services;
    QObjectCleanupHandler m_cleanupHandler;

protected:
    RpcServiceProvider();
    void processMessage(RpcSocket *apSocket, const RpcMessage &aMessage);

public:
    virtual ~RpcServiceProvider();
    virtual bool addService(RpcService *apService);
    virtual bool removeService(RpcService *apService);
    QByteArray getServiceName(RpcService *apService);
};

#endif // RPCSERVICEPROVIDER_H
