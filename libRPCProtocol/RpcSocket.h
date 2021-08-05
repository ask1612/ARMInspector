#ifndef RPCSOCKET_H
#define RPCSOCKET_H

#include <QObject>
#include <QIODevice>
#include <QPointer>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include <QJsonDocument>

#include "RpcServiceProvider.h"
#include "RpcMessage.h"
#include "RpcServiceReply.h"

#define DEFAULT_MSECS_REQUEST_TIMEOUT (30000)

class RpcSocket : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RpcSocket)

    QPointer<QIODevice> m_pDevice;
    QByteArray m_aBuffer;
    QHash<int, QPointer<RpcServiceReply>> m_replies;
    int m_defaultRequestTimeout;

protected:
    virtual void processRequestMessage(const RpcMessage &asMessage);

public:
    explicit RpcSocket(QObject *apParent = nullptr);
    explicit RpcSocket(QIODevice *apDevice, QObject *apParent = nullptr);
    virtual ~RpcSocket();

    virtual bool isValid() const;
    void setDefaultRequestTimeout(int aiMsecs);
    int getDefaultRequestTimeout() const;

    void setIODevice(QIODevice *pDevice);

signals:
    void messageReceived(const RpcMessage &asMessage);

private slots:
    virtual void processIncomingData();
    int findJsonDocumentEnd(const QByteArray &aJsonData);
    void writeData(const RpcMessage &asMessage);

public slots:
    virtual void notify(const RpcMessage &asMessage);
    virtual RpcMessage sendMessageBlocking(const RpcMessage &asMessage, int aMsecs = DEFAULT_MSECS_REQUEST_TIMEOUT);
    virtual RpcServiceReply *sendMessage(const RpcMessage &asMessage);
    RpcMessage invokeRemoteMethodBlocking(const QString &asMethod, int aMsecs, const QVariant &arg1 = QVariant(),
                                               const QVariant &arg2 = QVariant(), const QVariant &arg3 = QVariant(),
                                               const QVariant &arg4 = QVariant(), const QVariant &arg5 = QVariant(),
                                               const QVariant &arg6 = QVariant(), const QVariant &arg7 = QVariant(),
                                               const QVariant &arg8 = QVariant(), const QVariant &arg9 = QVariant(),
                                               const QVariant &arg10 = QVariant());
    RpcMessage invokeRemoteMethodBlocking(const QString &asMethod, const QVariant &arg1 = QVariant(),
                                               const QVariant &arg2 = QVariant(), const QVariant &arg3 = QVariant(),
                                               const QVariant &arg4 = QVariant(), const QVariant &arg5 = QVariant(),
                                               const QVariant &arg6 = QVariant(), const QVariant &arg7 = QVariant(),
                                               const QVariant &arg8 = QVariant(), const QVariant &arg9 = QVariant(),
                                               const QVariant &arg10 = QVariant());
    RpcServiceReply *invokeRemoteMethod(const QString &asMethod, const QVariant &arg1 = QVariant(),
                                             const QVariant &arg2 = QVariant(), const QVariant &arg3 = QVariant(),
                                             const QVariant &arg4 = QVariant(), const QVariant &arg5 = QVariant(),
                                             const QVariant &arg6 = QVariant(), const QVariant &arg7 = QVariant(),
                                             const QVariant &arg8 = QVariant(), const QVariant &arg9 = QVariant(),
                                             const QVariant &arg10 = QVariant());
};

#endif // RPCSOCKET_H
