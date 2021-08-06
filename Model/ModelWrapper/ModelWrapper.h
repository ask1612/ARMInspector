
/******************************************************************************* 
 * 
 *      Класс ModelWrapper - командная  обёртка, которая используется 
 *      при обмене данными  между сервером и клиентом.    
 * 
 * 
 ******************************************************************************/

#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H

#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QtCore/QObject>
#include <QMetaEnum>

class ModelWrapper : public JsonSerializable {

    Q_GADGET
    Q_ENUMS(Command)
    Q_ENUMS(Model)
public:
    //Список команд 

    enum Command {
        NOP,
        LOGIN,
        GET_LIST_MODELS,
        GET_MODEL,
        DEL_MODEL,
        ADD_CONNECTION,
        ADD_NEW_USER,
        ADD_NEW_MODEL,
        UPDATE_MODEL,
        EDIT_USER,
        CHANGE_PASSWORD,
        SERVER_RESPONSE,
        WAIT_SERVER_RESPONSE,
        SET_SESSION_ID,
        CALL_PROCEDURE
    };


    //Список моделей 

    enum Model {
        Unknown,
        User,
        Book,
        Msg,
        Act,
        Prepare,
        Review,
        Penalty,
        Mro,
        MroView,
        Nsi,
        ContextData,
        ContextOut,
        Report,
        ReportOut,
        RptRow,
        RptColumn,
        RptColumnView,
        UserView,
        Inspection,
        InspectionView
    };




    ///Список команд   c названием. Название используется в качестве  шапки 
    ///в командной обёртке при конструировании её с параметром команды.
    const QHash<Command, QString> ListCommand = {
        {Command::LOGIN, "Авторизация пользователя."},
        {Command::GET_LIST_MODELS, "Выполнить SQL запрос."},
        {Command::ADD_CONNECTION, "Добавить подключение к базе данных."},
        {Command::ADD_NEW_USER, "Добавить нового пользователя."},
        {Command::ADD_NEW_MODEL, "Добавить новую запись."},
        {Command::CHANGE_PASSWORD, "Изменить пароль пользователя."},
        {Command::EDIT_USER, "Редактировать данные пользователя."},
        {Command::UPDATE_MODEL, "Редактировать млдель."},
        {Command::GET_MODEL, "Получить экземпляр модели."},
        {Command::DEL_MODEL, "Удалить  экземпляр модели."},
        {Command::SERVER_RESPONSE, "Сообщение  сервера."},
        {Command::WAIT_SERVER_RESPONSE, "Ждать ответ  сервера."},
        {Command::SET_SESSION_ID, "Установить идентификатор сессии."},
        {Command::CALL_PROCEDURE, "Вызвать хранимую процедуру SQL"},
        {Command::NOP, "Холостая операция."}
    };
    //Названия моделей

    static QHash<Model, QString> map() {
        QHash<Model, QString> ListModel = {
            {Model::User, "user"},
            {Model::UserView, "v_user"},
            {Model::Mro, "mro"},
            {Model::Book, "book"},
            {Model::Msg, "msg"},
            {Model::Act, "act"},
            {Model::Prepare, "prepare"},
            {Model::Review, "review"},
            {Model::Penalty, "penalty"},
            {Model::MroView, "v_mro"},
            {Model::Inspection, "inspection"},
            {Model::InspectionView, "v_inspection"},
            {Model::RptRow, "reportrow"},
            {Model::RptColumn, "reportcol"},
            {Model::RptColumnView, "v_reportcol"},
            {Model::Report, "getCount_NewKoAP"},
            {Model::ReportOut, "getCount_NewKoAP"},
            {Model::ContextData, "getContextCount_NewKoAP"},
            {Model::ContextOut, "getContextCount_NewKoAP"},
            {Model::Nsi, "nsi_"}
        };
        return ListModel;
    }



    ///Конструктор.
    explicit ModelWrapper();
    ///Конструктор.
    /// @param cmd Команда, котрую необходимо выполнить
    explicit ModelWrapper(const Command& cmd);
    /// Деструктор.
    virtual ~ModelWrapper();
    ///Установить заголовок.
    /// @param head Шапка (заголовок) командной обёртки.
    void setHead(const QString& head);
    ///Записать данные.
    /// @param data Данные.
    void setData(const QString& data);
    ///Записать результат.
    /// @param success Результат выполнения операции(успех или неуспех).
    void setSuccess(const bool& success);
    ///Записать сообщение.
    /// @param message Сообщение.
    void setMessage(const QString& message);
    ///Получить заголовок.
    /// @return Заголовок. 
    const QString& getHead() const;
    ///Получить данные.
    /// @return Данные. 
    const QString& getData() const;
    ///Получить результат запроса.
    /// @return Успех или неуспех запроса. 
    const bool& getSuccess() const;
    ///Получить  сообщение.
    /// @return Сообщение. 
    const QString& getMessage() const;
    ///Считать данные JSON объекта в объект модели.
    /// @param jsonObj JSON объект.
    void read(const QJsonObject & jsonObj);
    ///Записать  данные объекта модели в JSON объект. 
    /// @param jsonObj JSON объект.
    void write(QJsonObject & jsonObj) const;
    ///Инициализировать идентификатор сессии.
    /// @param asSessionID Идентификатор сессии.
    void setSessionID(const int& asSessionID);
    ///Получить  идентификатор сессии.
    /// @return Идентификатор сессии. 
    const int& getSessionID() const;


    ///Получить команду.
    ///Используется при сериализации объекта.
    ///return Возвращает команду в виде строки.
    const QString getCommand() const;
    ///Получить команду.
    ///return Возвращает команду  в виде элемента перечисления Enum.  
    ModelWrapper::Command getEnumCommand() const;
    ///Установить команду.
    ///@param cmd Комманда в виде элемента перечисления Enum.
    void setCmd(ModelWrapper::Command cmd);
    ///Установить команду.
    ///Используется при сериализации объекта.
    /// @param cmd Команда в виде строки.
    void setCommand(const QString &cmd);


    ///Получить команду.
    ///return Возвращает model  в виде элемента перечисления Enum.  
    ModelWrapper::Model getEnumModel() const;
    ///Установить команду.
    ///@param mdl Модель в виде элемента перечисления Enum.
    void setEnumModel(ModelWrapper::Model mdl);
    ///Установить команду.
    ///Используется при сериализации объекта.
    /// @param mdl Модель в виде строки.
    void setModel(const QString &mdl);
    ///Получить модель.
    ///Используется при сериализации объекта.
    ///return Возвращает модель в виде строки.
    const QString getModel() const;

private:
    ///Заголовок сообщения.
    QString head_;
    ///идентификатор сессии, открытый для работы пользователя на сервере.
    int sessionID_;
    ///Комманда, которую необходимр выполнить серверу или обработать или
    ///тоже выполнить клиенту; 
    Command command_;
    ///Модель данных; 
    Model model_;

    ///Данные.
    QString data_;
    ///Успех или неуспех выполнения команды.
    bool success_;
    ///Сообщение.
    QString message_;

};

#endif /* MODELWRAPPER_H */

