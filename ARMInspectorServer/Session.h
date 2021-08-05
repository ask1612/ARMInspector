/****************************************************************************
 **
 **         Класс  Session для организации сессий подключаемых
 *           к серверу клиентов.
 **
 ****************************************************************************/

/* 
 * File:   Session.h
 * Author: ASK
 *
 * Created on 15 декабря 2019 г., 20:10
 */

#ifndef SESSION_H
#define SESSION_H
#include <QtCore>
#include "RpcAbstractServer.h"
#include "RpcService.h"
#include "RpcTCPServer.h"

#include <QTcpServer>
#include "Worker.h"
#include "Seance.h"
#include <QSharedPointer>

class Session : public QObject {
    Q_OBJECT

public:
    ///Конструктор.
    Session();
    /// Конструктор.
    /// @param pClientSocket Указатель на сокет клиента.
    /// @param id Идентивикаор сесси, создаентся но основе идентификатора клиента
    Session(const RpcSocket * pClientSocket, int id);
    ///Деструктор.
    virtual ~Session();
    const int& getSID() const;
    void readyData(QString);




    ///Список сессий.
    static QVector<Session*> m_aInstances;
    /// Создать новый сеанс работы.
    /// @param asQuery Данные.
    void addSeance(QString asQuery);
    ///создать подключение к базеданных
    bool addConnection(const int&);
signals:
    /// Сигнал готовности данных 
    /// @param Указатель на сокет клиента.
    /// @param Данные.
    void onReadyResult(const RpcSocket *, QString);
    public
Q_SLOTS:
    /// Удалить сеанс работы. 
    /// @param apSeance Указатель на сеанс работы.
    /// @param asQuery Данные.
    static void handleRes(QString asQuery);
    //void notifyCurrentClient(QString asString);

private:
    ///Идентификатор сессии.
    int m_aSessionID;
    ///Указатель на сокет клиент-серверного соединения. 
    const RpcSocket *m_pClientSocket;
    ///Указатель на сеанс. 
    Seance *m_pSeance;
    DBManager *m_pDBManager;



};

#endif /* SESSION_H */

