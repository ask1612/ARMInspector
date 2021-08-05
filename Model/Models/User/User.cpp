/****************************************************************************
 **
 **             Класс модели пользователя User.
 **
 ****************************************************************************/

/* 
 * File:   User.cpp
 * Author: 1
 * 
 * Created on 20 ноября 2019 г., 15:47
 */

#include "User/User.h"

ModelWrapper::Model User::model_={ModelWrapper::Model::User};
///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

User::User() : id_(0), fio_(""), inspection_(0), name_(""), password_(""),
status_(0), role_(0), access_(0), claim_(0), position_(0) {
}
///-----------------------------------------------------------------------------
///
///         Стандартный деструктор.
///          
///-----------------------------------------------------------------------------

User::~User() {
}
///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void User::setId(const qint64& id) {
    id_ = id;
};

void User::setFio(const QString& fio) {
    fio_ = fio;
};

void User::setInspection(const qint64& inspection) {
    inspection_ = inspection;
};

void User::setName(const QString& name) {
    name_ = name;
};

void User::setPassword(const QString& password) {
    password_ = password;
};

void User::setStatus(const qint64& status) {
    status_ = status;
};

void User::setRole(const qint64& role) {
    role_ = role;
};

void User::setAccess(const qint64& access) {
    access_ = access;
};

void User::setClaim(const qint64& claim) {
    claim_ = claim;
};

void User::setPosition(const qint64& position) {
    position_ = position;
};

const qint64& User::getId() const {
    return id_;
};

const QString& User::getFio() const {
    return fio_;
};

const qint64& User::getInspection() const {
    return inspection_;
};

const QString& User::getName() const {
    return name_;
};

const QString& User::getPassword()const {
    return password_;
};

const qint64& User::getStatus() const {
    return status_;
};

const qint64& User::getRole() const {
    return role_;
};

const qint64& User::getAccess() const {
    return access_;
};

const qint64& User::getClaim() const {
    return claim_;
};

const qint64& User::getPosition() const {
    return position_;
};
///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void User::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=User::getFieldArray();
    array<QString, 10> fld = User::getFields();

    this->setId(jsonObj[fld[User::Column::ID]].toInt());
    this->setFio(jsonObj[fld[User::Column::FIO]].toString());
    this->setInspection(jsonObj[fld[User::Column::ID_INSPECTION]].toInt());
    this->setName(jsonObj[fld[User::Column::NAME]].toString());
    this->setPassword(jsonObj[fld[User::Column::PASSWORD]].toString());
    this->setStatus(jsonObj[fld[User::Column::STATUS]].toInt());
    this->setRole(jsonObj[fld[User::Column::ROLE]].toInt());
    this->setAccess(jsonObj[fld[User::Column::ACCESS]].toInt());
    this->setClaim(jsonObj[fld[User::Column::CLAIM]].toInt());
    this->setPosition(jsonObj[fld[User::Column::POSITION]].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void User::write(QJsonObject &jsonObj) const {
    array<QString, 10> fld = User::getFields();

    jsonObj[fld[User::Column::ID]] = this->getId();
    jsonObj[fld[User::Column::FIO]] = this->getFio();
    jsonObj[fld[User::Column::ID_INSPECTION]] = this->getInspection();
    jsonObj[fld[User::Column::NAME]] = this->getName();
    jsonObj[fld[User::Column::PASSWORD]] = this->getPassword();
    jsonObj[fld[User::Column::STATUS]] = this->getStatus();
    jsonObj[fld[User::Column::ROLE]] = this->getRole();
    jsonObj[fld[User::Column::ACCESS]] = this->getAccess();
    jsonObj[fld[User::Column::CLAIM]] = this->getClaim();
    jsonObj[fld[User::Column::POSITION]] = this->getPosition();
};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant User::getData(const int& position) const {

    switch (position) {
        case User::Column::ID:
            return this->getId();
        case User::Column::FIO:
            return this->getFio();
        case User::Column::ID_INSPECTION:
            return this->getInspection();
        case User::Column::NAME:
            return this->getName();
        case User::Column::PASSWORD:
            return this->getPassword();
        case User::Column::STATUS:
            return this->getStatus();
        case User::Column::ROLE:
            return this->getRole();
        case User::Column::ACCESS:
            return this->getAccess();
        case User::Column::CLAIM:
            return this->getClaim();
        case User::Column::POSITION:
            return this->getPosition();
        default:
            return 0;
            break;
    }
};

///-----------------------------------------------------------------------------
///
///         Записать  данные в любое з поле класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

void User::setData(const int& position, const QVariant& value) {
    switch (position) {
        case User::Column::ID:
            this->setId(value.toInt());
            break;
        case User::Column::FIO:
            this->setFio(value.toString());
            break;
        case User::Column::ID_INSPECTION:
            this->setInspection(value.toInt());
            break;
        case User::Column::NAME:
            this->setName(value.toString());
            break;
        case User::Column::PASSWORD:
            this->setPassword(value.toString());
            break;
        case User::Column::STATUS:
            this->setStatus(value.toInt());
            break;
        case User::Column::ROLE:
            this->setRole(value.toInt());
            break;
        case User::Column::ACCESS:
            this->setAccess(value.toInt());
            break;
        case User::Column::CLAIM:
            this->setClaim(value.toInt());
            break;
        case User::Column::POSITION:
            this->setPosition(value.toInt());
            break;
        default:
            break;
    }

};

///-----------------------------------------------------------------------------
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void User::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "User::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, USER_COLUMN> fld = User::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case User::Column::ID:
                    asSqlQuery->bindValue(":" + fld[User::Column::ID], this->getId());
                    break;
                case User::Column::FIO:
                    asSqlQuery->bindValue(":" + fld[User::Column::FIO], this->getFio());
                    break;
                case User::Column::ID_INSPECTION:
                    asSqlQuery->bindValue(":" + fld[User::Column::ID_INSPECTION], this->getInspection());
                    break;
                case User::Column::NAME:
                    asSqlQuery->bindValue(":" + fld[User::Column::NAME], this->getName());
                    break;
                case User::Column::PASSWORD:
                    asSqlQuery->bindValue(":" + fld[User::Column::PASSWORD], this->getPassword());
                    break;
                case User::Column::STATUS:
                    asSqlQuery->bindValue(":" + fld[User::Column::STATUS], this->getStatus());
                    break;
                case User::Column::ROLE:
                    asSqlQuery->bindValue(":" + fld[User::Column::ROLE], this->getRole());
                    break;
                case User::Column::ACCESS:
                    asSqlQuery->bindValue(":" + fld[User::Column::ACCESS], this->getAccess());
                    break;
                case User::Column::CLAIM:
                    asSqlQuery->bindValue(":" + fld[User::Column::CLAIM], this->getClaim());
                    break;
                case User::Column::POSITION:
                    asSqlQuery->bindValue(":" + fld[User::Column::POSITION], this->getPosition());
                    break;
            }
        }
    }
}

///-----------------------------------------------------------------------------
///
///         Изменить данные пользователя. 
///
///
///-----------------------------------------------------------------------------

const QString& User::update() {
    //qInfo() << "User::update()";
    return query_.update()->set()->
//            field(User::Column::ID)->equally()->bind(User::Column::ID)->
            field(User::Column::FIO)->equally()->bind(User::Column::FIO)->
            field(User::Column::ID_INSPECTION)->equally()->bind(User::Column::ID_INSPECTION)->
            field(User::Column::NAME)->equally()->bind(User::Column::NAME)->
            field(User::Column::STATUS)->equally()->bind(User::Column::STATUS)->
            field(User::Column::ROLE)->equally()->bind(User::Column::ROLE)->
            field(User::Column::ACCESS)->equally()->bind(User::Column::ACCESS)->
            where()->field(User::Column::ID)->equally()->bind(User::Column::ID)->
            prepare();

}

///-----------------------------------------------------------------------------
///
///         Изменить пароль пользователя . 
///
///
///-----------------------------------------------------------------------------

const QString& User::changePassword() {
    //qInfo() << "User::changePassword()";
    return query_.update()->set()->
            field(User::Column::PASSWORD)->equally()->bind(User::Column::PASSWORD)->
            where()->field(User::User::Column::ID)->equally()->bind(User::User::Column::ID)->
            prepare();

}

///-----------------------------------------------------------------------------
///
///         Добавить пользователя . 
///
///
///-----------------------------------------------------------------------------

const QString& User::insert() {
    //qInfo() << "User::insert()";
    return query_.insert()->
            field(User::Column::FIO)->
            field(User::Column::ID_INSPECTION)->
            field(User::Column::NAME)->
            field(User::Column::STATUS)->
            field(User::Column::ROLE)->
            field(User::Column::ACCESS)->prepare();
}


///-----------------------------------------------------------------------------
///
///         Выбрать  пользователя по имени. 
///
///
///-----------------------------------------------------------------------------

const QString& User::selectByName() {
    //qInfo() << "User::selectByName()";
    return query_.select()->
            where()->field(User::User::Column::NAME)->equally()->bind(User::User::Column::NAME)->
            prepare();
}



