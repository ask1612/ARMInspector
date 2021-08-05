/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/****************************************************************************
 **
 **             Класс модели инспекции Inspection.
 **
 ****************************************************************************/

/* 
 * File:   Inspection.cpp
 * Author: kazun
 * 
 * 
 * Created on 3 апреля 2021 г., 21:58
 */

#include "Inspection/Inspection.h"

ModelWrapper::Model Inspection::model_ = {ModelWrapper::Model::Inspection};

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

Inspection::Inspection() {
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

Inspection::~Inspection() {
}
///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void Inspection::setId(const qint64& id) {
    id_ = id;
};

void Inspection::setName(const QString& name) {
    name_ = name;
};

void Inspection::setMro(const qint64& mro) {
    mro_ = mro;
};

const qint64& Inspection::getId()const {
    return id_;
};

const QString& Inspection::getName()const {
    return name_;
};

const qint64& Inspection::getMro()const {
    return mro_;
};

///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void Inspection::read(const QJsonObject &jsonObj) {

    array<QString, INSPECTION_COLUMN> fld = Inspection::getFields();
    this->setId(jsonObj[fld[Inspection::Column::ID]].toInt());
    this->setName(jsonObj[fld[Inspection::Column::NAME]].toString());
    this->setMro(jsonObj[fld[Inspection::Column::MRO]].toInt());
}

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void Inspection::write(QJsonObject &jsonObj) const {

    array<QString, INSPECTION_COLUMN> fld = Inspection::getFields();
    jsonObj[fld[Inspection::Column::ID]] = this->getId();
    jsonObj[fld[Inspection::Column::NAME]] = this->getName();
    jsonObj[fld[Inspection::Column::MRO]] = this->getMro();
};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant Inspection::getData(const int& position) const {

    switch (position) {
        case Inspection::Column::ID:
            return this->getId();
        case Inspection::Column::NAME:
            return this->getName();
        case Inspection::Column::MRO:
            return this->getMro();
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

void Inspection::setData(const int& position, const QVariant& value) {
    switch (position) {
        case Inspection::Column::ID:
            this->setId(value.toInt());
            break;
        case Inspection::Column::NAME:
            this->setName(value.toString());
            break;
        case Inspection::Column::MRO:
            this->setMro(value.toInt());
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

void Inspection::bindData(QSqlQuery* asSqlQuery) {
    ////qInfo() << "Mro::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, INSPECTION_COLUMN> fld = Inspection::getFields();
        for (int i = 0; i < list.size(); i++) {
            ////qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Inspection::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Inspection::Column::ID], this->getId());
                    break;
                case Inspection::Column::NAME:
                    asSqlQuery->bindValue(":" + fld[Inspection::Column::NAME], this->getName());
                    break;
                case Inspection::Column::MRO:
                    asSqlQuery->bindValue(":" + fld[Inspection::Column::MRO], this->getMro());
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

const QString& Inspection::insert() {
    ////qInfo() <<  query_.insert()->field(Inspection::Column::NAME)->
    //        field(Inspection::Column::MRO)->
    //        prepare();
    return query_.insert()->field(Inspection::Column::NAME)->
            field(Inspection::Column::MRO)->
            prepare();
}

///-----------------------------------------------------------------------------
///
///         Изменить данные инспекции. 
///
///
///-----------------------------------------------------------------------------

const QString& Inspection::update() {
    ////qInfo() << "Inspection::update()";
    return query_.update()->set()->
            //            field(User::Column::ID)->equally()->bind(User::Column::ID)->
            field(Inspection::Column::NAME)->equally()->bind(Inspection::Column::NAME)->
            field(Inspection::Column::MRO)->equally()->bind(Inspection::Column::MRO)->
            where()->field(Inspection::Column::ID)->equally()->bind(Inspection::Column::ID)->
            prepare();

}
