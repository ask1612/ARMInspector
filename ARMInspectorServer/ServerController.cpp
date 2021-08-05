/****************************************************************************
 **
 **         Реализация методов класса  ServerController.
 **
 ****************************************************************************/

#include "ServerController.h"
#include "User/User.h"
#include "JsonSerializer.h"
#include <iostream>
#include <QNetworkProxy>
#include "ServerMessage.h"
#include <QJsonArray>
//Максимальное количество подключений к северу.
#define MAX_CONNECTION 100


//Счётчик подключений.
int ServerController::m_aCounter = {0};
//Список освободившихся номеров  подключений.
QVector<int> ServerController::m_aListCounter = {};

////
QMutex ServerController::mutex_;


/// Конструктор.
/// @param parent Родительский объект.

ServerController::ServerController(QObject *parent) : RpcService(parent) {
    qDebug() << "CREATE SERVICE";
    // Сигнально-слотовое, извещающее о подключении клиента
    connect(this, &ServerController::clientConnected, [ = ] (const RpcSocket * apClientSocket){
        if (m_aCounter >= MAX_CONNECTION && isEmptyListCounter()) {
            QString responce = createResponce(apClientSocket, Message::MAXIMUM_CONNECTIONS_EXCEEDED);
                    notifyCurrentClient(apClientSocket, responce);
        } else {
            //Создать сессию  и добавить её в список открытых.
            //Присвоить ID сессии. 
            addSession(apClientSocket);

        }
    });
    // Сигнально-слотовое соединение, извещающее об отключении клиента
    connect(this, &ServerController::clientDisconnected, [ = ] (const RpcSocket * apClientSocket){
        qDebug() << "Client disconnected" << apClientSocket->isValid();
        //Удалить сессию.
        removeSession(apClientSocket, m_aListSession[*m_aConnectedClients.find(apClientSocket)]);
    });
}

///Создать сессию  и добавить её в список открытых.
///Присвоить ID сессии. 
///@param apClientSocket Указатель на сокет клиента.

void ServerController::addSession(const RpcSocket * apClientSocket) {
    //Проверить сокет.
    if (!apClientSocket->isValid()) {
        //Если соект не корректен то операцию открытия сесси прекратить.
        qDebug() << "Can`t add session" << apClientSocket->isValid();
        return;
    }
    //Получить номер подключения.
    m_aConnectedClients.insert(apClientSocket, ServerController::getConnectionCounter());
    //Создать сессию.
    Session * pSession = new Session(apClientSocket, *m_aConnectedClients.find(apClientSocket));
    //Проверить, создана ли сессия.
    if (pSession == nullptr) {
        //Сессия не создана.
        //Подготовить сообщение о невозможности создать сессию.
        QString responce = createResponce(apClientSocket, Message::CANNOT_CREATE_SESSION);
        //Уведомить клиента.
        notifyCurrentClient(apClientSocket, responce);
        return;
    }
    qDebug() << "Session ID  " << *m_aConnectedClients.find(apClientSocket);
    //Добавить сессию в список открытых.
    m_aListSession.insert(*m_aConnectedClients.find(apClientSocket), pSession);
    //Сессия создана  успешно.
    //Создать сигнально-слотовое соединение между сессией и контроллером сервера,которое сигнализирет,
    //что сессия готова передать контроллеру информацию
    connect(pSession, SIGNAL(onReadyResult(const RpcSocket*, QString)), this, SLOT(notifyCurrentClient(const RpcSocket*, QString)));
    //Подготовить клиенту сообщение, что клиент  подключен к серверу, ему открыта сессия и просвоено ID сессии.
    QString responce = createResponce(apClientSocket, Message::SESSION_IS_OPEN);
    //Передать сообщение  клиенту.
    notifyCurrentClient(apClientSocket, responce);
    //if (m_pSession->addConnection(*m_aConnectedClients.find(apClientSocket))) {
    //    responce = createResponce(apClientSocket, Message::ADD_CONNECTION_SUCCESS);
    //Передать сообщение  клиенту.
    //    notifyCurrentClient(apClientSocket, responce);
    //} else {
    //    responce = createResponce(apClientSocket, Message::ADD_CONNECTION_FAILURE);
    //Передать сообщение  клиенту.
    //    notifyCurrentClient(apClientSocket, responce);
    //}

}

/// Удалить  сессию.
/// @param apClientSocket Указатель на сокет клиента.

void ServerController::removeSession(const RpcSocket * apClientSocket, const Session * apSession) {
    //Проверить сокет.
    if (!apClientSocket->isValid()) {
        //Если сокет не корректен то операцию закрытия сесси прекратить.
        qDebug() << "Can`t close session" << apClientSocket->isValid();
        return;
    }
    //Проверить сессию .
    if (apSession == nullptr) {
        //Сессия не существует.
        //Подготовить сообщение о невозможности удалить  сессию.
        QString responce = createResponce(apClientSocket, Message::CANNOT_DELETE_SESSION);
        //Если сокет корректен, уведомить клиента.
        notifyCurrentClient(apClientSocket, responce);
        return;
    }
    //Если сессия существует,
    //удалить сигнально-слотовое соединение между сессией и контроллером сервера.
    disconnect(apSession, SIGNAL(onReadyResult(const RpcSocket*, QString)), apClientSocket, 0);
    //Убрать сессию из списка открытых. 
    m_aListSession.remove(*m_aConnectedClients.find(apClientSocket));
    //Удпалить сессию.
    delete apSession;
    //Добавить номер подключения в список освободившихся номеров.
    ServerController::m_aListCounter.push_back(*m_aConnectedClients.find(apClientSocket));
    //Удалить подключение из списка подключений.
    m_aConnectedClients.remove(apClientSocket);
}


//Деструктор

ServerController::~ServerController() {

}




///Получить номер подключения.

int ServerController::getConnectionCounter() {
    //Использовать  освободившиеся номера. 
    auto useListCounter = []() {
        //Берём из списка самый верхний номер.

        int counter = ServerController::m_aListCounter.back();
        //Удаляем его из списка.
        ServerController::m_aListCounter.pop_back();
        //Возвращем номер подключения.
        return counter;
    };

    return (isEmptyListCounter())
            //Если нет свободных номеров, увиличиваем счётчик подключений. 
            ? ++ServerController::m_aCounter
            //Иначе используем номер из списка свободных номеров.
            : useListCounter();
}


///Проверить пустой или нет список освободившихся номеров.

bool ServerController::isEmptyListCounter() {

    return ServerController::m_aListCounter.isEmpty();
}
///Старт сервера.

bool ServerController::start() {
    qInfo() << "ServerController::start()";
    QNetworkProxy proxy;
    QNetworkProxy::setApplicationProxy(proxy);
    m_pSocketServer = new QTcpServer();
    m_pServer = new RpcTCPServer();
    if (m_pServer->listen(QString(QHostAddress::LocalHost), 7071)) {
        connect(m_pServer, SIGNAL(onClientConnected(const RpcSocket*)), SIGNAL(clientConnected(const RpcSocket*)));
        connect(m_pServer, SIGNAL(onClientDisconnected(const RpcSocket*)), SIGNAL(clientDisconnected(const RpcSocket*)));
        m_pServer->addService(this);
    } else {
        qCritical() << QString("Can't listen on %1").arg(ARM_BRAND);
        qCritical() << m_pServer->errorString();
        return false;
    }
    return true;
}


/// Выполнить  запрос клиента.
/// @param asQuery  Строка запроса.

void ServerController::execServerCommand(const QString & asQuery) {
    //Создать  командную обёртку. 
    ModelWrapper wrapper;
    //Конвертировать данные, пришедшие  от клиента в JSON объект.
    JsonSerializer::parse(asQuery, wrapper);
    qDebug() << "execServerCommand Session ID " << wrapper.getSessionID();

    for (auto pSession : Session::m_aInstances) {
        if (pSession->getSID() == wrapper.getSessionID()) {
            pSession->addSeance(asQuery);
        }
    }
    return;
}

/// Подготовить ответ сервера. Используется, когда не требуется запуск сеанса.
/// Контроллер сам может сформировать  ответ клиенту.
/// Такая ситуация возникает при продключении  клиента  к серверу.
/// Контроллер сервера без привлечения других ресурсов и создания сенса работы
/// с базой данных самостоятельно  создает сессию подключенному клиенту
/// и присваивает ей  ID. После успешного создания сессии контроллер сервера 
/// передает ID сессии   клиенту .
/// В случае невозможности создать или удалить  сессию  контроллер также
/// самостоятельно  сообщает об этом подключенному клиенту

/// @param apClientSocket Указатель на сокет.
/// @param asMsg Идентификатор собщения.
/// @return Сообщение клиенту в виде строки.  

QString ServerController::createResponce(const RpcSocket * apClientSocket, Message asMsg) {

    //Получить параметры сообщения.
    ServerMessage::Result result = ServerMessage::outPut(asMsg);
    //Создать командную обёртку.
    ModelWrapper wrapper(result.cmd);
    if (result.cmd == ModelWrapper::Command::SET_SESSION_ID) {
        wrapper.setSessionID(*m_aConnectedClients.find(apClientSocket));
    }
    //Установить сообщение.
    wrapper.setMessage(result.str);
    if (result.cmd == ModelWrapper::Command::ADD_CONNECTION) {
        wrapper.setSessionID(*m_aConnectedClients.find(apClientSocket));
        qDebug() << wrapper.getSessionID();
        //Установить сообщение.
        wrapper.setMessage(QString(result.str).arg(*m_aConnectedClients.find(apClientSocket)));
    }
    //Утановить результат выполнения команды
    wrapper.setSuccess(result.success);
    //Упаковать  весь запрос в строку
    QString responce = JsonSerializer::serialize(wrapper);
    return responce;
}

/// Уведомить  клиента и передать данные. 
/// Сообщение передаётся конкретному клиенту по его сокету.
/// @param apClientSocket Сокет клиента, которому возвращается информация. 
/// @param asString Данные в командной оболочке сериализованные в строку. 

void ServerController::notifyCurrentClient(const RpcSocket * apClientSocket, QString asString) {
    //QMutexLocker lock(&ServerController::mutex_);
    qDebug() << apClientSocket;
    //Прверить, корректен ли сокет.
    if (!apClientSocket->isValid()) {
        //Если сокет не корректен, операцию по уведомлению клиента прекратить. 
        // qDebug() << "Can`t notify client" << apClientSocket->isValid();
        return;
    }
    //qDebug() << "I notify client" << apClientSocket->isValid();
    /// Сокет корректен.
    ///Убрать старое клиент-серверное соединение.
    disconnect(this, SIGNAL(notify(RpcMessage)), 0, 0);
    ///Создать новое клиент-серверное соединение.
    connect(this, SIGNAL(notify(RpcMessage)), apClientSocket, SLOT(notify(RpcMessage)));
    ///Софрмировать ответ клиенту.
    RpcMessage request = RpcMessage::createRequest(asString);
    ///Сигнализировать о готовности ответа.
    emit notify(request);
}

