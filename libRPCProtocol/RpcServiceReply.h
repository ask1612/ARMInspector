#ifndef RPCSERVICEREPLY_H
#define RPCSERVICEREPLY_H

#include <QObject>
#include <QNetworkReply>

#include "RpcMessage.h"

class RpcServiceReply : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RpcServiceReply)
    RpcMessage m_request;
    RpcMessage m_response;

public:
    explicit RpcServiceReply(QObject *apParent = nullptr);
    virtual ~RpcServiceReply();

    RpcMessage request() const;
    RpcMessage response() const;

    void setRequest(const RpcMessage &aRequest);
    void setResponse(const RpcMessage &aResponse);

signals:
    void finished();
};

#endif // RPCSERVICEREPLY_H
