/****************************************************************************
 **
 **             Класс DBManager для работы с базой данных.
 **
 ****************************************************************************/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QMutexLocker>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <RpcSocket.h>
#include "ModelWrapper.h"
#include "ServerMessage.h"
#include "ItemContainer.h"
#include <array>
#include "User/User.h"
#include "Mro/Mro.h"
#include "Mro/MroView.h"
#include "Report/Report.h"
#include "RptRow/RptRow.h"
#include "RptColumn/RptColumn.h"
#include "RptColumn/RptColumnView.h"
#include "User/UserView.h"
#include "Inspection/Inspection.h"
#include "Inspection/InspectionView.h"
#include "Nsi/Nsi.h"
#include "ContextData/ContextData.h"

using namespace std;

class DBManager : public QObject {
    Q_OBJECT
public:

    /// Стандартный конструктор.
    /// @param apParent Родитель.
    DBManager(QObject *apParent = nullptr);

    ///Деструктор.
    virtual ~DBManager();

    ///Инициализировать указатель на класс командной обёртки.
    void setModelWrapper(ModelWrapper* wrapper);
    ///Получить  указатель на класс командной обёртки.
    const ModelWrapper* getModelWrapper() const;



    /// Подключиться к базе данных .Открыть  базу данных.
    bool addDataBase();

    /// Авторизация пользователя.
    void login();
    ///Добавить  пользователя.
    void addUser();
    ///Проверить имя  пользователя.
    bool isUserName(const QString&, const QSqlDatabase&);
    ///Редактировать   пользователя.
    void updateUser();
    ///Изменить пароль    пользователя.
    void changePassword();
    /// Получить список моделей.
    void getListModels();
    template<typename T> void getListModels();

    /// Вызвать хранимую процедуру.
    void callProcedure();
    template<typename T, typename TOUT> void callProcedure();
    /// Удалить  модель.
    void deleteModel();
    ///удалить модель из списка
    template<typename T> void deleteModel();

    /// Редактировать  модель.
    void updateModel();
    template<typename T> void updateModel();
    ///добавить модель
    void addModel();
    template<typename T> void addModel();
    /// Получить  модель.
    void getModel();
    template<typename T> void getModel();
    ///Получить  запись из базы данных.
    template<typename T> T getRecord(const QString& queryStr, const QSqlDatabase&);
    ///Получить  записи из базы данных.
    template<typename T> ItemContainer<T> getAllRecordS(const QSqlDatabase&);
    ///удалить запись
    template<typename T> void delRecord(const T&, const QString&, const QSqlDatabase&);
    ///Проверить  подключение к базе данных.
    template<typename T> QSqlDatabase connectDB();
    /// Отключить клиента от сервера
    /// @param apClientSocket Указатель на сокет клиент-серверного соединения.
    void removeDatabase();
    /// Выполнить Sql запрос.
    ///void execSqlquery();
public:
    static QSqlDatabase database(const QString& connectionName = QLatin1String(QSqlDatabase::defaultConnection));


    /// Выполнить Sql запрос.
    //template<typename T> void execSqlquery();
signals:
    ///Сигнал завершения работы.
    /// @param asResult Результат выполнения запроса 
    void finished(QString asResult);

private:
    static QMutex s_databaseMutex;
    static QHash<QThread*, QHash<QString, QSqlDatabase>>s_instances;
    ///Указатель на командную обёртку модели.
    ModelWrapper *m_pModelWrapper;
    ///Мьютех блокировки внешних воздействий. 
    QMutex m_Mutex;
    ///DB. 
    QSqlDatabase m_Db;
};
#include "DBManager_IMPL.h"

#endif // DBMANAGER_H
