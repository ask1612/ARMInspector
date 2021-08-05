/****************************************************************************
 **
 **         Класс  ServerController.
 **
 ****************************************************************************/

#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include "RpcAbstractServer.h"
#include "RpcService.h"
#include "RpcTCPServer.h"
#include "DBManager.h"

#include <QTcpServer>

#include <QDebug>
#include "Worker.h"
#include "ModelWrapper.h"
#include "Session.h"

class ServerController : public RpcService {

    Q_OBJECT
    Q_CLASSINFO("serviceName", "RPCServer")
    /// Service core.
    RpcTCPServer * m_pServer {
        nullptr
    };
    /// Socket of client connection with the service.
    QTcpServer * m_pSocketServer{nullptr};

public:
    //Счётчик подключений клиентов к базе данных.
    static int m_aCounter;
    static QMutex mutex_;
    //Список освободившихся номеров
    static QVector<int> m_aListCounter;
    //Список  подключений к серверу
    QHash<const RpcSocket*, int> m_aConnectedClients;


    ServerController(QObject *parent = nullptr);
    ~ServerController();
    ///Проверить пустой или нет список освободившихся номеров.
    bool isEmptyListCounter();
    ///Получить номер подключения.
    int getConnectionCounter();

    ///Старт сервера.
    bool start();

    QString createResponce(const RpcSocket * apClientSocket, Message asMsg);
    /// Создать сессию.
    /// @param apClientSocket Указатель на сокет клиента.
    void addSession(const RpcSocket * apClientSocket);
    /// Удалить  сессию.
    /// @param apClientSocket Указатель на сокет клиента.
    void removeSession(const RpcSocket * apClientSocket, const Session * apSession);

signals:

    /// Сигнал излучается в случае необходимости передать сообщение клиенту.
    /// @param Сообщение клиенту. 
    void notify(RpcMessage);
    /// Сигнал излучается в случае подключения клиента.
    void clientConnected(const RpcSocket * apSocketClient);
    /// Сигнал излучется в случае отключения клиента.
    void clientDisconnected(const RpcSocket * apSocketClient);

    public
Q_SLOTS:
    /// Выполнить Sql запрос клиента.
    /// @param asQuery  запрос.
    void execServerCommand(const QString & asQuery);
    void notifyCurrentClient(const RpcSocket * apClientSocket, QString asString);

private:
    //Указатель на сессию.
    Session *m_pSession{nullptr};
    //Список  открытых сессий. Ключ- ID сессии, Значение-указатель на сессию.
    QHash<const int, Session * > m_aListSession;

};

#endif // SERVERCONTROLLER_H
