/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mro.cpp
 * Author: kazun_as
 * 
 * Created on 20 апреля 2021 г., 15:36
 */

#include "Mro/Mro.h" 

ModelWrapper::Model Mro::model_ = {ModelWrapper::Model::Mro};

Mro::Mro() : id_(0), name_(""), inspection_(0) {
}

Mro::~Mro() {
}

void Mro::setId(const qint64& id) {
    id_ = id;
};

void Mro::setName(const QString& name) {
    name_ = name;
};

void Mro::setInspection(const qint64& inspection) {
    inspection_ = inspection;
};

const qint64& Mro::getId() const {
    return id_;
};

const QString& Mro::getName() const {
    return name_;
};

const qint64& Mro::getInspection() const {
    return inspection_;
};

///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void Mro::read(const QJsonObject &jsonObj) {

    array<QString, MRO_COLUMN> fld = Mro::getFields();
    this->setId(jsonObj[fld[Mro::Column::ID]].toInt());
    this->setName(jsonObj[fld[Mro::Column::NAME]].toString());
    this->setInspection(jsonObj[fld[Mro::Column::INSPECTION]].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void Mro::write(QJsonObject &jsonObj) const {

    array<QString, MRO_COLUMN> fld = Mro::getFields();
    jsonObj[fld[Mro::Column::ID]] = this->getId();
    jsonObj[fld[Mro::Column::NAME]] = this->getName();
    jsonObj[fld[Mro::Column::INSPECTION]] = this->getInspection();

};


///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant Mro::getData(const int& position) const {

    switch (position) {
        case Mro::Column::ID:
            return this->getId();
        case Mro::Column::NAME:
            return this->getName();
        case Mro::Column::INSPECTION:
            return this->getInspection();
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

void Mro::setData(const int& position, const QVariant& value) {
    switch (position) {
        case Mro::Column::ID:
            this->setId(value.toInt());
            break;
        case Mro::Column::NAME:
            this->setName(value.toString());
            break;
        case Mro::Column::INSPECTION:
            this->setInspection(value.toInt());
            break;
        default:
            break;
    }

};
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Mro::bindData(QSqlQuery* asSqlQuery) {
    ////qInfo() << "Mro::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, MRO_COLUMN> fld = Mro::getFields();
        for (int i = 0; i < list.size(); i++) {
            ////qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Mro::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Mro::Column::ID], this->getId());
                    break;
                case Mro::Column::NAME:
                    asSqlQuery->bindValue(":" + fld[Mro::Column::NAME], this->getName());
                    break;
                case Mro::Column::INSPECTION:
                    asSqlQuery->bindValue(":" + fld[Mro::Column::INSPECTION], this->getInspection());
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}


///-----------------------------------------------------------------------------
///
///         Добавить запись в справочник . 
///
///
///-----------------------------------------------------------------------------

const QString& Mro::insert() {
    ////qInfo() << "Mro::insert()";
    return query_.insert()->field(Mro::Column::NAME)->
            field(Mro::Column::INSPECTION)->
            prepare();
}

///-----------------------------------------------------------------------------
///
///         Изменить данные МРО. 
///
///
///-----------------------------------------------------------------------------

const QString& Mro::update() {
    ////qInfo() << "Mro::update()";
    return query_.update()->set()->
            //            field(User::Column::ID)->equally()->bind(User::Column::ID)->
            field(Mro::Column::NAME)->equally()->bind(Mro::Column::NAME)->
            field(Mro::Column::INSPECTION)->equally()->bind(Mro::Column::INSPECTION)->
            where()->field(Mro::Column::ID)->equally()->bind(Mro::Column::ID)->
            prepare();

}
