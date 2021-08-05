#include "RpcServiceReply.h"

RpcServiceReply::RpcServiceReply(QObject *apParent)
    : QObject(apParent)
{
}

RpcServiceReply::~RpcServiceReply()
{

}

void RpcServiceReply::setRequest(const RpcMessage &aRequest)
{
    m_request = aRequest;
}

void RpcServiceReply::setResponse(const RpcMessage &aResponse)
{
    m_response = aResponse;
}

RpcMessage RpcServiceReply::request() const
{
    return m_request;
}

RpcMessage RpcServiceReply::response() const
{
    return m_response;
}
