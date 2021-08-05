/****************************************************************************
 **
 **         Реализация методов класса  Session.
 **
 ****************************************************************************/

/* 
 * File:   Session.cpp
 * Author: ASK
 * 
 * Created on 15 декабря 2019 г., 20:10
 */

#include "Session.h"
///Список сессий.
QVector<Session*> Session::m_aInstances;

Session::Session() {
}
/// Конструктор.Создать сессию.
/// @param pClientSocket Указатель на сокет клиента.
/// @param id Идентификатор сессии.

Session::Session(const RpcSocket * pClientSocket, int id) {
    m_aInstances.push_back(this);
    m_aSessionID = id;
    m_pClientSocket = pClientSocket;
    qDebug() << "Session  opened";
    //m_pDBManager = new DBManager();

}

///Деструктор. Завершить сессию.

Session::~Session() {
    ///Искать сессию в списке.
    QVector<Session*>::iterator p = std::find(m_aInstances.begin(), m_aInstances.end(), this);
    ///Если сессия найдена, убрать её из списка.
    if (p != m_aInstances.end())
        m_aInstances.erase(p);
    qDebug() << "Session  deleted";
    //delete m_pDBManager;
}
///создать подключение к базеданных

bool Session::addConnection(const int& asId ) {
    //Создать  командную обёртку. 
    ModelWrapper wrapper;
    wrapper.setSessionID(asId);
    m_pDBManager->setModelWrapper(&wrapper);
    return m_pDBManager->addDataBase();
}

/// Создать новый сеанс работы.
/// @param asQuery Данные, полученные от клиента.

void Session::addSeance(QString asQuery) {
    //Создать командную обёртку.
    ModelWrapper wrapper;
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [ &wrapper](Message msg) {
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        wrapper.setMessage(result.str);
        wrapper.setSuccess(result.success);
    };

    //Конвертировать данные от клиента в JSON объект.
    JsonSerializer::parse(asQuery, wrapper);

    //Генерировать ID для подключения к базе данных, для исключения одинаковых
    ///имён подключений к базе данных.
    //wrapper.setSessionID(wrapper.getSessionID()*1000 + Seance::m_aInstances.size() + 1);
    ///сериализовать командную обёртку.
    QString wrapperString = JsonSerializer::serialize(wrapper);
    ///Создать новый сенс работы с базой данных.
    m_pSeance = new Seance(wrapperString);
    if (m_pSeance != nullptr) {
        ///Отключить старые соединения.
        disconnect(m_pSeance, SIGNAL(onReadyResult( QString)), 0, 0);
        ///Создать соединение, сигнализирующее, что сенс возвращает данные
        //connect(m_pSeance, SIGNAL(onReadyResult(Seance*, QString)), this, SLOT(removeSeance(Seance*, QString)));
        m_pSeance->addThread();
    } else {
        ///Не возможно создать сеанс работы с базой данных.
        setResult(Message::CANNOT_CREATE_SEANCE);
        QString asErrorString = JsonSerializer::serialize(wrapper);
        //Сообщить об этом контроллеру сервера;
        emit onReadyResult(m_pClientSocket, asErrorString);
    }
}





/// Обработать возвращённый результат  запроса и закрыть сеанс.
/// @param asQuery возвращенные данные. 

void Session::handleRes(QString asQuery) {
    //qDebug() << "Session::handleRes";
    //Создать  командную обёртку. 
    ModelWrapper wrapper;
    //Конвертировать данные, пришедшие  от клиента в JSON объект.
    JsonSerializer::parse(asQuery, wrapper);
    //Искать  сеанс в списке.
    //QVector<Seance*>::iterator p = std::find(Seance::m_aInstances.begin(), Seance::m_aInstances.end(), apSeance);
    ///Если сеанс найден, то удалть его
    //    if (p != Seance::m_aInstances.end()) {

    for (auto pSession : Session::m_aInstances) {
        if (pSession->getSID() == wrapper.getSessionID()) {
            pSession->readyData(asQuery);
        }
    }
    //if (m_aSessionID == wrapper.getSessionID()) {
    //Сообщить контроллеру сервера, что обработка запроса завершена;
    //    if (m_pClientSocket->isValid()) {
    //        qDebug() << "ClientSocket:" << m_pClientSocket;
    //        ModelWrapper wrapper;
    //        JsonSerializer::parse(asQuery, wrapper);
    //        qDebug() << "Session::handleResult:" << wrapper.getSessionID();

    //        emit onReadyResult(m_pClientSocket, asQuery);
    //    }
    //    delete m_pSeance;
    //}
}

///Получить  идентификатор сессии.
/// @return Идентификатор сессии. 

const int& Session::getSID() const {
    return m_aSessionID;
}

void Session::readyData(QString asQuery) {
    emit onReadyResult(m_pClientSocket, asQuery);
}




