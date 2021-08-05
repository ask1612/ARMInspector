#include "RpcSocket.h"
#include "RpcServiceRequest.h"


RpcServiceRequest::RpcServiceRequest()
{
}

RpcServiceRequest::~RpcServiceRequest()
{
}

RpcServiceRequest::RpcServiceRequest(const RpcServiceRequest &aRpcServiceRequest)
{
    m_request = aRpcServiceRequest.m_request;
    m_socket = aRpcServiceRequest.m_socket;
}

RpcServiceRequest::RpcServiceRequest(const RpcMessage &aRequest,
                                               RpcSocket *apSocket)
{
    m_request = aRequest;
    m_socket = apSocket;
}

RpcServiceRequest &RpcServiceRequest::operator=(const RpcServiceRequest &other)
{
    m_request = other.m_request;
    m_socket = other.m_socket;
    return *this;
}

bool RpcServiceRequest::isValid() const
{
    return (m_request.isValid() && !m_socket.isNull());
}

RpcMessage RpcServiceRequest::request() const
{
    return m_request;
}

RpcSocket *RpcServiceRequest::socket() const
{
    return m_socket;
}

bool RpcServiceRequest::respond(QVariant aReturnValue)
{
    if (!m_socket) {
        qJsonRpcDebug() << "socket was closed";
        return false;
    }

    RpcMessage response =
        m_request.createResponse(RpcService::convertReturnValue(aReturnValue));
    return respond(response);
}

bool RpcServiceRequest::respond(const RpcMessage &aResponse)
{
    if (!m_socket) {
        qJsonRpcDebug() << "socket was closed";
        return false;
    }

    QMetaObject::invokeMethod(m_socket, "notify", Q_ARG(RpcMessage, aResponse));
    return true;
}
