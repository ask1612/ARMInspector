#ifndef RPCSERVICEREQUEST_H
#define RPCSERVICEREQUEST_H

#include <QPointer>
#include <QMetaObject>
#include <QDebug>

#include "RpcMessage.h"

class RpcSocket;
class RpcServiceRequest
{
    RpcMessage m_request;
    QPointer<RpcSocket> m_socket;

public:
    RpcServiceRequest();
    RpcServiceRequest(const RpcServiceRequest &aRpcServiceRequest);
    RpcServiceRequest(const RpcMessage &aRequest, RpcSocket *apSocket);
    RpcServiceRequest &operator=(const RpcServiceRequest &aRpcServiceRequest);
    ~RpcServiceRequest();

    bool isValid() const;
    RpcMessage request() const;
    RpcSocket *socket() const;

    bool respond(const RpcMessage &aResponse);
    bool respond(QVariant aReturnValue);
};

#endif // RPCSERVICEREQUEST_H
