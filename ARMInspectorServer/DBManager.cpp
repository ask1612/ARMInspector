/****************************************************************************
 **
 ** Реализация  методов  класса DBManager.
 **
 ****************************************************************************/

#include "DBManager.h"
#include <QSqlError>
QMutex DBManager::s_databaseMutex;
QHash<QThread*, QHash<QString, QSqlDatabase>> DBManager::s_instances;


///-----------------------------------------------------------------------------
///         Стандартный конструктор.
///          @param apParent Родитель.
///-----------------------------------------------------------------------------

DBManager::DBManager(QObject *apParent) : QObject(apParent) {
}

DBManager::~DBManager() {
    auto name = QString().setNum(m_pModelWrapper->getSessionID()) + "_" + QString::number((quint64) QThread::currentThread(), 16);
    QSqlDatabase::database(name).close();
    QSqlDatabase::removeDatabase(name);
}


///-----------------------------------------------------------------------------

///Инициализировать указатель на класс командной обёртки .
///-----------------------------------------------------------------------------

void DBManager::setModelWrapper(ModelWrapper* wrapper) {

    m_pModelWrapper = wrapper;
}
///-----------------------------------------------------------------------------
///
///             Получить  указатель на класс командной обёртки.
///
///-----------------------------------------------------------------------------

const ModelWrapper* DBManager::getModelWrapper() const {

    return m_pModelWrapper;
}
///-----------------------------------------------------------------------------
///
///             database(const QString& connectionName)
///
///-----------------------------------------------------------------------------

QSqlDatabase DBManager::database(const QString& connectionName) {
    QMutexLocker locker(&s_databaseMutex);
    QThread *thread = QThread::currentThread();

    // if we have a connection for this thread, return it
    auto it_thread = s_instances.find(thread);
    if (it_thread != s_instances.end()) {
        auto it_conn = it_thread.value().find(connectionName);
        if (it_conn != it_thread.value().end()) {
            return it_conn.value();
        }
    }

    // otherwise, create a new connection for this thread
    QSqlDatabase connection = QSqlDatabase::cloneDatabase(
            QSqlDatabase::database(connectionName),
            QString("%1_%2").arg(connectionName).arg((qint64) thread));

    // open the database connection
    // initialize the database connection
    if (!connection.open()) {
        throw std::runtime_error("Unable to open the new database connection.");
    }

    s_instances[thread][connectionName] = connection;
    return connection;
}


///-----------------------------------------------------------------------------
///
///              Подключиться к базе данных. Открыть  базу данных.
///
///-----------------------------------------------------------------------------

bool DBManager::addDataBase() {
    QThread *thread = QThread::currentThread();
    //Блокировать ресурсы SQL от использования их  другими пользователями. 
    //static QMutex mutex;
    //QMutexLocker lock(&mutex);
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](Message msg) {
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);
    };
    const QString DRIVER("QODBC3");
    if (!QSqlDatabase::isDriverAvailable(DRIVER)) {
        setResult(Message::DATABASE_DRIVER_IS_NOT_AVAILABLE);
        return false;
    }
    //Добавить  подключение клиента в список подключений к базе данных 
    //Добавить  подключение клиента в список подключений к базе данных 
    //auto name = "my_db_" + QString::number((quint64) QThread::currentThread(), 16);
    auto name = QString().setNum(m_pModelWrapper->getSessionID()) + "_" + QString::number((quint64) QThread::currentThread(), 16);
    qDebug() << "add database  " << name;

    //  QSqlDatabase database = QSqlDatabase::addDatabase(DRIVER, QString().setNum(m_pModelWrapper->getSessionID()));
    QSqlDatabase connection = QSqlDatabase::addDatabase(DRIVER, name);
    if (connection.isValid()) {
        connection.setDatabaseName("DRIVER={MySQL ODBC 5.1 Driver};SERVER=localhost;DATABASE=gu_delinq;Uid=test;Pwd=tst;");
        //connection.setDatabaseName("DRIVER={MySQL ODBC 8.0 Unicode Driver};SERVER=localhost;DATABASE=gu_delinq;Uid=test;Pwd=tst;");
        //database.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");
        //database.setDatabaseName("arm");
        //database.setUserName("");
        //database.setHostName("localhost");
        //database.setPort(3305);
        //database.setPassword("");
        //Открыть базу данных
        if (!connection.open()) {
            qDebug() << "FAILURE.db is not opened";

            setResult(Message::UNABLE_OPEN_DATABASE);
            return false;
        }
        //qDebug() << "SUCEESS. db is opened";
        qDebug() << "CONNECT " << QString().setNum(m_pModelWrapper->getSessionID());
        //База данных не открыта.Авторизация не возможна.
        //s_instances[thread][name] = connection;
        //m_Db = connection;
        return true;
    } else {
        setResult(Message::UNABLE_CONNECT_DATABASE);
        return false;
    }

}



///-----------------------------------------------------------------------------
///
///             Авторизация пользователя.
///
///-----------------------------------------------------------------------------

void DBManager::login() {
    //Блокировать ресурсы SQL от использования их  другими потоками. 
    //static QMutex mutex;
    //QMutexLocker lock(&mutex);
    //Загрузить параметры команды.
    QJsonObject param;
    JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
    //Имя пользователя.
    QString asLogin = param["name"].toString();
    //Пароль.
    QString asPassword = param["password"].toString();
    //Создать модель данных User
    User user;
    user.setName(asLogin);
    //дополнение к сообщению
    QString attach = "<br><a style='color:red'> ";
    attach += user.getName() + "</a>";
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](User user, Message msg, QString attach) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(QString(result.str).arg(attach));
        m_pModelWrapper->setSuccess(result.success);


    };
    if (!asLogin.isEmpty()&&!asPassword.isEmpty()) {
        //подключение к  базе данных.
        QSqlDatabase connection = connectDB<User>();
        if (!m_pModelWrapper->getSuccess()) {
            //        if (!connectDB<User>()) {
            //qDebug() << "DB not connected";
            return;
        }
        //База данных открыта. Можно проводить авторизацию пользователя. 

        QSqlQuery queryStatementInfo(connection);
        //Подготовить запрос на чтение данных из  базы.
        QString strGetStatementInfo = "select * from user where name='" + asLogin + "'";
        //Выполнить зыпрос к базе данных.
        if (!queryStatementInfo.exec(strGetStatementInfo)) {
            attach = "Ошибка:  " + strGetStatementInfo;
            setResult(user, Message::SQL_ERROR, attach);
            return;
        }
        //Проверить, есть ли в базе данных хотя бы одна запись, удовлетворяющая запросу    
        if (!queryStatementInfo.next()) {
            //Пользователя с таким именем нет в базе данных. 
            //Если это admin , то добавить его и установить пароль по умолчанию
            if (asLogin == "admin") {
                //qDebug() << asLogin;
                QString pasword_hash = QString(QCryptographicHash::hash(("adm11"), QCryptographicHash::Md5).toHex());
                QString sqlquery_string = QString("INSERT INTO user(name,password)"
                        " VALUES ('admin','") + pasword_hash + QString("')");
                //qDebug() << sqlquery_string;

                if (!queryStatementInfo.exec(sqlquery_string)) {
                    attach = "Ошибка:  " + strGetStatementInfo;
                    setResult(user, Message::CANNOT_ADD_ADMIN_USER, attach);
                    return;
                } else {
                    setResult(user, Message::ADD_ADMIN_USER_SUCCESS, attach);
                    //Пользователь admin успешно добавлен в базу данных
                    return;
                }
            } else {
                setResult(user, Message::USER_IS_NOT_FOUND, attach);
                return;
            }
        }
        //JSON объект для хранения записи базы данных.
        QJsonObject recordObject;
        //Скопировать запись базы данных в JSON объект.
        for (int x = 0; x < queryStatementInfo.record().count(); x++) {
            ////qDebug() << queryStatementInfo.value(x);
            recordObject.insert(queryStatementInfo.record().fieldName(x), QJsonValue::fromVariant(queryStatementInfo.value(x)));
        }
        ///Считать данные JSON объекта  в объект класса User.  
        user.read(recordObject);
        //Имя пользователя найдено. Прверить пароль прользователя.Получить хеш пароля.
        QString pasword_hash = QString(QCryptographicHash::hash((asPassword.toStdString().c_str()), QCryptographicHash::Md5).toHex());
        //Сравнить его с хеш в базе данных
        if (pasword_hash.compare(user.getPassword().trimmed(), Qt::CaseSensitive) != 0) {
            //Пользователь не прошёл авторизацию. Пароль неверен. 
            setResult(user, Message::USER_LOGIN_FAILURE, attach);
            return;
        }
        //Пароль введённый пользователем и пароль в базе данных совпали. Пользователь  прошёл авторизацию. 
        setResult(user, Message::USER_LOGIN_SUCCESS, attach);
        return;
    } else {
        if (asLogin.isEmpty()) {
            setResult(user, Message::USER_NAME_EMPTY, attach);
            return;
        }
        setResult(user, Message::USER_PASSWORD_EMPTY, attach);
        return;
    }
}


///-----------------------------------------------------------------------------
///
///             Вызвать хранимую процедуру
///
///-----------------------------------------------------------------------------

void DBManager::callProcedure() {
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::Report:
        {
            callProcedure<Report, ReportOut>();
        }
            break;
        case ModelWrapper::Model::ContextData:
        {
            callProcedure<ContextData, ContextOut>();
        }
            break;
        default:
        {
            auto setResult = [this](Message msg, QString attach) {
                //Установить сообщение и результат выполнения команды.
                ServerMessage::Result result = ServerMessage::outPut(msg);
                m_pModelWrapper->setMessage(QString(result.str).arg(attach));
                m_pModelWrapper->setSuccess(result.success);
            };
            //qDebug() << "Unknown model";
            QString attach = "<a style='color:red'> deleteModel</a>";
            setResult(Message::UNKMOWN_MODEL, attach);
        }
            break;

    }

}
///-----------------------------------------------------------------------------
///
///             Удалить модель
///
///-----------------------------------------------------------------------------

void DBManager::deleteModel() {

    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::User:
        {
            deleteModel<User>();
        }
            break;
        case ModelWrapper::Model::UserView:
        {
            deleteModel<UserView>();
        }
            break;
        case ModelWrapper::Model::Mro:
        {
            deleteModel<Mro>();
        }
            break;
        case ModelWrapper::Model::Inspection:
        {
            deleteModel<Inspection>();
        }
            break;
        case ModelWrapper::Model::RptColumn:
        {
            deleteModel<RptColumn>();
        }
            break;
        case ModelWrapper::Model::RptRow:
        {
            deleteModel<RptRow>();
        }
            break;
        case ModelWrapper::Model::Nsi:
        {
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            //            m_pModelWrapper->setData(param[DATA].toString());
            deleteModel<Nsi>();
        }
            break;
        default:
        {
            auto setResult = [this](Message msg, QString attach) {
                //Установить сообщение и результат выполнения команды.
                ServerMessage::Result result = ServerMessage::outPut(msg);
                m_pModelWrapper->setMessage(QString(result.str).arg(attach));
                m_pModelWrapper->setSuccess(result.success);
            };
            //qDebug() << "Unknown model";
            QString attach = "<a style='color:red'> deleteModel</a>";
            setResult(Message::UNKMOWN_MODEL, attach);
        }
            break;
    }
}


///-----------------------------------------------------------------------------
///
///             Добавить модель
///
///-----------------------------------------------------------------------------

void DBManager::addModel() {
    //qInfo() << "Получаем модель";
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::Nsi:
        {
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //номер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            m_pModelWrapper->setData(param[DATA].toString());
            ////qInfo() << param[DATA].toString();
            addModel<Nsi>();
        }
            break;
        case ModelWrapper::Model::Mro:
        {
            ////qInfo() << param[DATA].toString();
            addModel<Mro>();
        }
            break;
        case ModelWrapper::Model::Inspection:
        {
            ////qInfo() << param[DATA].toString();
            addModel<Inspection>();
        }
            break;
        case ModelWrapper::Model::RptColumn:
        {
            ////qInfo() << param[DATA].toString();
            addModel<RptColumn>();
        }
            break;
        case ModelWrapper::Model::RptRow:
        {
            ////qInfo() << param[DATA].toString();
            addModel<RptRow>();
        }
            break;
        default:
        {
            auto setResult = [this](Message msg, QString attach) {
                //Установить сообщение и результат выполнения команды.
                ServerMessage::Result result = ServerMessage::outPut(msg);
                m_pModelWrapper->setMessage(QString(result.str).arg(attach));
                m_pModelWrapper->setSuccess(result.success);
            };
            //qDebug() << "Unknown model";
            QString attach = "<a style='color:red'> addModel</a>";
            setResult(Message::UNKMOWN_MODEL, attach);
        }
            break;
    }
}


///-----------------------------------------------------------------------------
///
///             Редактировать модель
///
///-----------------------------------------------------------------------------

void DBManager::updateModel() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::Nsi:
        {
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            m_pModelWrapper->setData(param[DATA].toString());
            updateModel<Nsi>();
        }
            break;
        case ModelWrapper::Model::Mro:
        {
            updateModel<Mro>();
        }
            break;
        case ModelWrapper::Model::Inspection:
        {
            updateModel<Inspection>();
        }
            break;
        case ModelWrapper::Model::RptColumn:
        {
            updateModel<RptColumn>();
        }
            break;
        case ModelWrapper::Model::RptRow:
        {
            updateModel<RptRow>();
        }
            break;
        default:
        {
            auto setResult = [this](Message msg, QString attach) {
                //Установить сообщение и результат выполнения команды.
                ServerMessage::Result result = ServerMessage::outPut(msg);
                m_pModelWrapper->setMessage(QString(result.str).arg(attach));
                m_pModelWrapper->setSuccess(result.success);
            };
            //qDebug() << "Unknown model";
            QString attach = "<a style='color:red'> updateModel</a>";
            setResult(Message::UNKMOWN_MODEL, attach);
        }
            break;
    }
}


///-----------------------------------------------------------------------------
///
///             Получить модель
///
///-----------------------------------------------------------------------------

void DBManager::getModel() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::User:
        {
            getModel<User>();
        }
            break;
        case ModelWrapper::Model::UserView:
        {
            getModel<UserView>();
        }
            break;
        case ModelWrapper::Model::Inspection:
        {
            getModel<Inspection>();
        }
            break;
        case ModelWrapper::Model::RptColumn:
        {
            getModel<RptColumn>();
        }
            break;
        case ModelWrapper::Model::RptRow:
        {
            getModel<RptRow>();
        }
            break;
        case ModelWrapper::Model::Mro:
        {
            getModel<Mro>();
        }
            break;
        case ModelWrapper::Model::MroView:
        {
            getModel<MroView>();
        }
            break;
        case ModelWrapper::Model::Nsi:
        {
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            getModel<Nsi>();
        }
            break;
        default:
        {
            auto setResult = [this](Message msg, QString attach) {
                //Установить сообщение и результат выполнения команды.
                ServerMessage::Result result = ServerMessage::outPut(msg);
                m_pModelWrapper->setMessage(QString(result.str).arg(attach));
                m_pModelWrapper->setSuccess(result.success);
            };
            //qDebug() << "Unknown model";
            QString attach = "<a style='color:red'> getModel</a>";
            setResult(Message::UNKMOWN_MODEL, attach);
        }
            break;
    }
}
///-----------------------------------------------------------------------------
///
///                 Получить список моделей
///
///-----------------------------------------------------------------------------

void DBManager::getListModels() {
    //Получаем модель.
    ModelWrapper::Model model = m_pModelWrapper->getEnumModel();
    //Выбрать модель, данные которой необходимо запросить. 
    switch (model) {
        case ModelWrapper::Model::User:
        {
            getListModels<User>();
        }
            break;
        case ModelWrapper::Model::Mro:
        {
            getListModels<Mro>();
        }
            break;
        case ModelWrapper::Model::MroView:
        {
            getListModels<MroView>();
        }
            break;
        case ModelWrapper::Model::UserView:
        {
            getListModels<UserView>();
        }
            break;
        case ModelWrapper::Model::Inspection:
        {
            getListModels<Inspection>();
        }
            break;
        case ModelWrapper::Model::InspectionView:
        {
            getListModels<InspectionView>();
        }
            break;
        case ModelWrapper::Model::RptColumn:
        {
            getListModels<RptColumn>();
        }
            break;
        case ModelWrapper::Model::RptRow:
        {
            getListModels<RptRow>();
        }
            break;
        case ModelWrapper::Model::RptColumnView:
        {
            getListModels<RptColumnView>();
        }
            break;
        case ModelWrapper::Model::Nsi:
        {
            QJsonObject param;
            JsonSerializer::json_decode(m_pModelWrapper->getData(), param);
            //ноиер НСИ
            Nsi::num_ = param[NSI_NUM].toString();
            ////qDebug()<<"num_" << Nsi::num_;
            getListModels<Nsi>();
        }
            break;
        default:
        {
            auto setResult = [this](Message msg, QString attach) {
                //Установить сообщение и результат выполнения команды.
                ServerMessage::Result result = ServerMessage::outPut(msg);
                m_pModelWrapper->setMessage(QString(result.str).arg(attach));
                m_pModelWrapper->setSuccess(result.success);
            };
            //qDebug() << "Unknown model";
            QString attach = "<a style='color:red'> getListModels</a>";
            setResult(Message::UNKMOWN_MODEL, attach);
        }
            break;
    }
}



///-----------------------------------------------------------------------------
///
///                      Отключить клиента от сервера
///                      @param apClientSocket 
///                      Указатель на сокет клиент-серверного соединения.
///
///-----------------------------------------------------------------------------

void DBManager::removeDatabase() {
    {
        auto name = QString().setNum(m_pModelWrapper->getSessionID()) + "_" + QString::number((quint64) QThread::currentThread(), 16);
        QSqlDatabase::database(name).close();
        QSqlDatabase::removeDatabase(name);
    }
}

///-----------------------------------------------------------------------------
///
///                     Изменить пароль  пользователя 
///
///-----------------------------------------------------------------------------

void DBManager::changePassword() {
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](User user, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);


    };
    //Создать модель данных User
    User user;
    JsonSerializer::parse(m_pModelWrapper->getData(), user);
    //подключение к  базе данных.
    QSqlDatabase connection = connectDB<User>();
    if (!m_pModelWrapper->getSuccess()) {
        return;
    }

    //База данных открыта. Можно проводить авторизацию пользователя. 
    QSqlQuery query(connection);
    QString pasword_hash = QString(QCryptographicHash::hash((user.getPassword().toStdString().c_str()), QCryptographicHash::Md5).toHex());
    user.setPassword(pasword_hash);
    query.prepare(user.changePassword());
    user.bindData(&query);
    if (query.exec()) {
        setResult(user, Message::PASSWORD_CHANGE_SUCCESS);
        //qDebug() << user.getName();
        //qDebug() << user.getId();
        //qDebug() << "update user password  succes: ";
    } else {
        setResult(user, Message::PASSWORD_CHANGE_FAILURE);
        //qDebug() << "update user password  failed: " << query.lastError();
        //qDebug() << user.getName();
    }
    return;
}


///-----------------------------------------------------------------------------
///
///                     Редактировать пользователя 
///
///-----------------------------------------------------------------------------

void DBManager::updateUser() {
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](User user, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);


    };
    //Создать модель данных User
    User user;
    JsonSerializer::parse(m_pModelWrapper->getData(), user);
    ////qDebug() << myquery;
    //подключение к  базе данных.
    QSqlDatabase connection = connectDB<User>();
    if (!m_pModelWrapper->getSuccess()) {
        return;
    }
    //База данных открыта. Можно проводить авторизацию пользователя. 
    QSqlQuery query(connection);
    ////qDebug() << user.getName();
    query.prepare(user.update());
    user.bindData(&query);

    if (query.exec()) {
        setResult(user, Message::USER_EDIT_SUCCESS);
        //qDebug() << user.getName();
        //qDebug() << user.getId();
        //qDebug() << "update user  succes: ";
    } else {
        setResult(user, Message::USER_EDIT_FAILURE);
        //qDebug() << "update person failed: " << query.lastError();
        //qDebug() << user.getName();
    }
    return;
}

///-----------------------------------------------------------------------------
///
///         Проверить имя пользователя
///
///-----------------------------------------------------------------------------

bool DBManager::isUserName(const QString& name, const QSqlDatabase& con) {
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    User user;
    user.setName(name);
    auto setResult = [this](User user, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str + QString("<br><a style='color:red'> ") +
                user.getName() +
                QString("</a> <br> Необходимо выбрать другое имя."));
        m_pModelWrapper->setSuccess(result.success);
    };
    QSqlQuery query(con);
    query.prepare(user.selectByName());
    user.bindData(&query);
    if (!query.exec()) {
        setResult(user, Message::USER_ADD_FAILURE);
        return false;
    }
    if (!query.next()) {
        setResult(user, Message::USER_NAME_NO);
        return false;
    }
    QJsonObject recordObject;
    ///Экземпляр объекта класса T, который будет  сериализоваться.
    for (int x = 0; x < query.record().count(); x++) {
        recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
        //qDebug() << "DBManager::isUserName(User user)";
    }
    ///Считать запись базы данных  в объект класса T.  
    user.read(recordObject);
    //qInfo() << user.getName();
    setResult(user, Message::USER_NAME_IS);
    return true;
}

///-----------------------------------------------------------------------------
///
///         Добавить нового пользователя
///
///-----------------------------------------------------------------------------

void DBManager::addUser() {
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [this](User user, Message msg) {
        //Подготовить данные.
        QString json = JsonSerializer::serialize(user);
        m_pModelWrapper->setData(json);
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        m_pModelWrapper->setMessage(result.str);
        m_pModelWrapper->setSuccess(result.success);


    };
    //Создать модель данных User
    User user;
    JsonSerializer::parse(m_pModelWrapper->getData(), user);
    //подключение к  базе данных.
    QSqlDatabase connection = connectDB<User>();
    if (!m_pModelWrapper->getSuccess()) {
        return;
    }
    if (isUserName(user.getName(),connection)) {
        return;
    }

    QString pasword_hash = QString(QCryptographicHash::hash((user.getPassword().toStdString().c_str()), QCryptographicHash::Md5).toHex());
    user.setPassword(pasword_hash);
    //qInfo() << user.insert();
    //База данных открыта. Можно проводить авторизацию пользователя. 

    QSqlQuery query(connection);
    query.prepare(user.insert());
    user.bindData(&query);

    //queryAdd.prepare("INSERT INTO user (fio,id_inspection,name,password,status,role,access)"
    //        " VALUES (:fio,:id_inspection,:name,:password,:status,:role,:access)");
    //queryAdd.bindValue(":fio", user.getFio());
    //queryAdd.bindValue(":id_inspection", user.getInspection());
    //queryAdd.bindValue(":name", user.getName());
    //Получить хеш пароля.
    //queryAdd.bindValue(":password", pasword_hash);
    //queryAdd.bindValue(":status", user.getStatus());
    //queryAdd.bindValue(":role", user.getRole());
    //queryAdd.bindValue(":access", user.getAccess());

    if (query.exec()) {
        //query.prepare("SELECT * FROM user WHERE ID = (SELECT max(ID) FROM user)");
        query.prepare(MQuery<User>::selectMaxID());
        if (!query.exec()) {
            setResult(user, Message::USER_ADD_FAILURE);
            return;
        }
        //Выборка данных.
        while (query.next()) {
            QJsonObject recordObject;
            ///Экземпляр объекта класса T, который будет  сериализоваться.
            for (int x = 0; x < query.record().count(); x++) {
                recordObject.insert(query.record().fieldName(x), QJsonValue::fromVariant(query.value(x)));
            }
            ///Считать запись базы данных  в объект класса T.  
            user.read(recordObject);
        }
        setResult(user, Message::USER_ADD_SUCCESS);
        //qDebug() << user.getName();
        //qDebug() << user.getId();
        //qDebug() << "add user  succes: ";
    } else {
        setResult(user, Message::USER_ADD_FAILURE);
        //qDebug() << "add person failed: " << query.lastError();
        //qDebug() << user.getName();
    }

    return;
}










