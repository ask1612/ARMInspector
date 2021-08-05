/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nsi.cpp
 * Author: kazun_as
 * 
 * Created on 23 апреля 2021 г., 16:15
 */

#include "Nsi/Nsi.h"
#include <QMessageBox>

ModelWrapper::Model Nsi::model_={ModelWrapper::Model::Nsi};

QString Nsi::num_ = {""};

Nsi::Nsi() {
}

Nsi::Nsi(const QString& num) {
    Nsi::num_ = num;
}

Nsi::~Nsi() {
}

void Nsi::setId(const qint64& id) {
    id_ = id;
};

void Nsi::setName(const QString& name) {
    name_ = name;
};

const qint64& Nsi::getId() const {
    return id_;
};

const QString& Nsi::getName() const {
    return name_;
};



///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void Nsi::read(const QJsonObject &jsonObj) {
    array<QString, NSI_COLUMN> fld = Nsi::getFields();
    this->setId(jsonObj[fld[Nsi::Column::ID]].toInt());
    this->setName(jsonObj[fld[Nsi::Column::NAME]].toString());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void Nsi::write(QJsonObject &jsonObj) const {
    array<QString, NSI_COLUMN> fld = Nsi::getFields();
    jsonObj[fld[Nsi::Column::ID]] = this->getId();
    jsonObj[fld[Nsi::Column::NAME]] = this->getName();

};


///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant Nsi::getData(const int& position) const {

    switch (position) {
        case Nsi::Column::ID:
            return this->getId();
        case Nsi::Column::NAME:
            return this->getName();
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

void Nsi::setData(const int& position, const QVariant& value) {
    switch (position) {
        case Nsi::Column::ID:
            this->setId(value.toInt());
            break;
        case Nsi::Column::NAME:
            this->setName(value.toString());
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

void Nsi::bindData(QSqlQuery* asSqlQuery) {
    ////qInfo() << "Nsi::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, NSI_COLUMN> fld = Nsi::getFields();
        for (int i = 0; i < list.size(); i++) {
            ////qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Nsi::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Nsi::Column::ID], this->getId());
                    break;
                case Nsi::Column::NAME:
                    asSqlQuery->bindValue(":" + fld[Nsi::Column::NAME], this->getName());
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

const QString& Nsi::insert() {
    ////qInfo() << "Nsi::insert()";
    return query_.insert()->field(Nsi::Column::NAME)->prepare();
}




///-----------------------------------------------------------------------------
///
///
///         Изменить данные записи NSI. 
///
///
///-----------------------------------------------------------------------------

const QString& Nsi::update() {
    ////qInfo() << "Nsi::update()";
    return query_.update()->set()->
//            field(Nsi::Column::ID)->equally()->bind(Nsi::Column::ID)->
            field(Nsi::Column::NAME)->equally()->bind(Nsi::Column::NAME)->
            where()->field(Nsi::Column::ID)->equally()->bind(Nsi::Column::ID)->prepare();

}
