#include "RpcServiceProvider.h"
#include "RpcSocket.h"

RpcServiceProvider::RpcServiceProvider()
{
}

RpcServiceProvider::~RpcServiceProvider()
{
}

QByteArray RpcServiceProvider::getServiceName(RpcService *apService)
{
    const QMetaObject *mo = apService->metaObject();
    for (int i = 0; i < mo->classInfoCount(); i++) {
        const QMetaClassInfo mci = mo->classInfo(i);
        if (mci.name() == QLatin1String("serviceName"))
            return mci.value();
    }

    return QByteArray(mo->className()).toLower();
}

bool RpcServiceProvider::addService(RpcService *apService)
{
    QByteArray serviceName = getServiceName(apService);
    if (serviceName.isEmpty()) {
        qJsonRpcDebug() << "service added without serviceName classinfo, aborting";
        return false;
    }

    if (m_services.contains(serviceName)) {
        qJsonRpcDebug() << "service with name " << serviceName << " already exist";
        return false;
    }

    apService->cacheInvokableInfo();
    m_services.insert(serviceName, apService);
    if (!apService->parent())
        m_cleanupHandler.add(apService);
    return true;
}

bool RpcServiceProvider::removeService(RpcService *apService)
{
    QByteArray serviceName = getServiceName(apService);
    if (!m_services.contains(serviceName)) {
        qJsonRpcDebug() << "can not find service with name " << serviceName;
        return false;
    }

    m_cleanupHandler.remove(m_services.value(serviceName));
    m_services.remove(serviceName);
    return true;
}

void RpcServiceProvider::processMessage(RpcSocket *apSocket, const RpcMessage &aMessage)
{
    switch (aMessage.type()) {
        case RpcMessage::Request:
        case RpcMessage::Notification: {
            QByteArray serviceName = aMessage.method().section(".", 0, -2).toLatin1();
            if (serviceName.isEmpty() || !m_services.contains(serviceName)) {
                if (aMessage.type() == RpcMessage::Request) {
                    RpcMessage error =
                        aMessage.createErrorResponse(ErrorCode::MethodNotFound,
                            QString("service '%1' not found").arg(serviceName.constData()));
                    apSocket->notify(error);
                }
            } else {
                RpcService *service = m_services.value(serviceName);
                service->setCurrentRequest(RpcServiceRequest(aMessage, apSocket));
                if (aMessage.type() == RpcMessage::Request)
                    QObject::connect(service, SIGNAL(result(RpcMessage)),
                                      apSocket, SLOT(notify(RpcMessage)), Qt::UniqueConnection);
                RpcMessage response = service->dispatch(aMessage);
                if (response.isValid())
                    apSocket->notify(response);
            }
        }
        break;

        case RpcMessage::Response:
            break;

        default: {
            RpcMessage error =
                aMessage.createErrorResponse(ErrorCode::InvalidRequest, QString("invalid request"));
            apSocket->notify(error);
            break;
        }
    };
}
