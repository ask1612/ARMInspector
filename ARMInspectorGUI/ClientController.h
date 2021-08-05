#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>

#include "CommandController.h"
#include "ServerClient.h"
#include "ModelWrapper.h"
#include "JsonSerializer.h"
#include "ItemContainer.h"
#include "WorkerClient.h"
#include "User/User.h"
#include "Mro/Mro.h"
#include "Nsi/Nsi.h"
class WorkerClient;
class ClientController : public QObject {

    Q_OBJECT
    Q_DISABLE_COPY(ClientController)
    /// Клиент.
    ServerClient *m_pServerClient {
        nullptr
    };
    /// Командный контроллер.
    CommandController *m_pCommandController{nullptr};
    /// Обработчик серверных сообщений
    WorkerClient *m_pWorkerClient{nullptr};

    /// Стандартный конструктор.
    /// @param Родительский класс.
    explicit ClientController(QObject *aParent = nullptr);

public:
    /// Получить экземпляр класса.
    /// @return Instance of a class.
    Q_INVOKABLE static ClientController &getInstance();
    /// Инициализировать командный контроллер клиента.
    /// @param apServerClient Клиент.
    void init(ServerClient *apServerClient);
    ///установить флаг  авторизации клиента
    void setLogged(bool asLogged);
    ///получить номер справочника
    const QString& getNsiNum();
    ///получить флаг  авторизации клиента
    bool getLogged();
    ///Получить пользователя сессии
    const User& getSessionUser();


signals:
    //template<typename T> void setModel(const T&);
    void ready();
    ///Cписок МРО подготовлен  
    void listMroReady(const QList<Mro>&);
    ///Cписок НСИ подготовлен  
    void listNsiReady(const QList<Nsi>&);
    ///получен ответ сервера
    void responseServer(const QString&);
    ///Cписок пользователей подготовлен  
    void listUserReady(const QList<UserView>&);
    ///Cписок инспекций подготовлен  
    void listInspectionsReady(const QList<Inspection>&);
    ///Данные пользователя  
    void userReady(const User&);
    ///Данные НСИ  
    void nsiReady(const Nsi&);

private slots:

    /// Обработать ответ сервера на   запрос клиента.
    /// @param asJson Ответ сервера в виде JSON
    /// объекта сериализованного в строку. 
    void processRequestServer(QString asJson);
    ///Установить идентификатор сессии
    void setSessionID(int asID);
    ///Установить сигнал готовности формы 
    void formReady();



public slots:
    void runServerCmd(const QString &asQuery);
    /// Выполнить запрос к  серверу на авторизацию пользователя.
    /// @param asLogin  Имя пользователя. 
    ///Установить пользователя сессии
    void setSessionUser(const User&);
    ///Ждать завершения предыдущей операции или сигнала старта.
    void waitReady();

private:
    int m_aSessionID{0};
    bool m_aLogged{false};
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;
    ///Пользователь, открывший сессию
    User m_aSessionUser;


};


#endif // CLIENTCONTROLLER_H
