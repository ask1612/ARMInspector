#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QIODevice>
#include <QDebug>

#include "RpcSocket.h"
#include "RpcServiceProvider.h"
#include "RpcService.h"

class CommandController : public QObject {

    Q_OBJECT
    Q_DISABLE_COPY(CommandController)

    /// RPC-сокет.
    RpcSocket * m_RpcSocket {
        nullptr
    };

public:
    /// Переопределенный конструктор.
    /// @param apIODevice Устройство ввода/вывода (QTcpSocket).
    /// @param apParent Родительский класс.
    CommandController(QIODevice *apIODevice, QObject *apParent = nullptr);

signals:
    /// Сигнал излучается после обработатки результата  выполнения  запроса к серверу.
    /// @param result Результат выполнения на сервере SQL запроса.
    void onProcessRequestServer(QString result);

private slots:
    /// Обработать входящее сообщение.
    /// @param asMessage Входящее сообщение.
    void messageProcessing(const RpcMessage &asMessage);
    /// Обработать результат  выполнения  запроса к   серверу. 
    //void processRequestServer();

public slots:
    /// Сделать  запрос к  серверу.
    /// @param asQuery SQL запрос.
    void requestServer(const QString &asQuery);

};

#endif // COMMANDCONTROLLER_H
