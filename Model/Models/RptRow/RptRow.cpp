/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptRow.cpp
 * Author: kazun_as
 * 
 * Created on 17 мая 2021 г., 13:00
 */

#include "RptRow.h"

ModelWrapper::Model RptRow::model_ = {ModelWrapper::Model::RptRow};

RptRow::RptRow() {
}

RptRow::~RptRow() {
}

///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void RptRow::setId(const qint64& id) {
    id_ = id;
};

void RptRow::setNpp(const QString& npp) {
    npp_ = npp;
};

void RptRow::setName(const QString& name) {
    name_ = name;
};

void RptRow::setFormula(const QString& formula) {
    formula_ = formula;
};

void RptRow::setRow(const qint64& row) {
    row_ = row;
};

const qint64& RptRow::getId() const {
    return id_;
};

const QString& RptRow::getNpp() const {
    return npp_;
};

const QString& RptRow::getName() const {
    return name_;
};

const QString& RptRow::getFormula() const {
    return formula_;
};

const qint64& RptRow::getRow() const {
    return row_;
};


///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void RptRow::read(const QJsonObject &jsonObj) {
    array<QString, RPTROW_COLUMN> fld = RptRow::getFields();
    this->setId(jsonObj[fld[RptRow::Column::ID]].toInt());
    this->setNpp(jsonObj[fld[RptRow::Column::NPP]].toString());
    this->setName(jsonObj[fld[RptRow::Column::NAME]].toString());
    this->setFormula(jsonObj[fld[RptRow::Column::FORMULA]].toString());
    this->setRow(jsonObj[fld[RptRow::Column::ROW]].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void RptRow::write(QJsonObject &jsonObj) const {
    array<QString, RPTROW_COLUMN> fld = RptRow::getFields();

    jsonObj[fld[RptRow::Column::ID]] = this->getId();
    jsonObj[fld[RptRow::Column::NPP]] = this->getNpp();
    jsonObj[fld[RptRow::Column::NAME]] = this->getName();
    jsonObj[fld[RptRow::Column::FORMULA]] = this->getFormula();
    jsonObj[fld[RptRow::Column::ROW]] = this->getRow();

};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant RptRow::getData(const int& position) const {

    switch (position) {
        case RptRow::Column::ID:
            return this->getId();
        case RptRow::Column::NPP:
            return this->getNpp();
        case RptRow::Column::NAME:
            return this->getName();
        case RptRow::Column::FORMULA:
            return this->getFormula();
        case RptRow::Column::ROW:
            return this->getRow();
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

void RptRow::setData(const int& position, const QVariant& value) {
    switch (position) {
        case RptRow::Column::ID:
            this->setId(value.toInt());
            break;
        case RptRow::Column::NPP:
            this->setNpp(value.toString());
            break;
        case RptRow::Column::NAME:
            this->setName(value.toString());
            break;
        case RptRow::Column::FORMULA:
            this->setFormula(value.toString());
            break;
        case RptRow::Column::ROW:
            this->setRow(value.toInt());
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

void RptRow::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "RptRow::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, RPTROW_COLUMN> fld = RptRow::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case RptRow::Column::ID:
                    asSqlQuery->bindValue(":" + fld[RptRow::Column::ID], this->getId());
                    break;
                case RptRow::Column::NPP:
                    asSqlQuery->bindValue(":" + fld[RptRow::Column::NPP], this->getNpp());
                    break;
                case RptRow::Column::NAME:
                    asSqlQuery->bindValue(":" + fld[RptRow::Column::NAME], this->getName());
                    break;
                case RptRow::Column::FORMULA:
                    asSqlQuery->bindValue(":" + fld[RptRow::Column::FORMULA], this->getFormula());
                    break;
                case RptRow::Column::ROW:
                    asSqlQuery->bindValue(":" + fld[RptRow::Column::ROW], this->getRow());
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

const QString& RptRow::insert() {
    //qInfo() << "RptRow::insert()";
    return query_.insert()->field(RptRow::Column::NPP)->
            field(RptRow::Column::NAME)->
            field(RptRow::Column::FORMULA)->
            field(RptRow::Column::ROW)->
            prepare();
}

///-----------------------------------------------------------------------------
///
///         Изменить данные инспекции. 
///
///
///-----------------------------------------------------------------------------

const QString& RptRow::update() {
    //qInfo() << "RptRow::update()";
    return query_.update()->set()->
            //            field(User::Column::ID)->equally()->bind(User::Column::ID)->
            field(RptRow::Column::NPP)->equally()->bind(RptRow::Column::NPP)->
            field(RptRow::Column::NAME)->equally()->bind(RptRow::Column::NAME)->
            field(RptRow::Column::FORMULA)->equally()->bind(RptRow::Column::FORMULA)->
            field(RptRow::Column::ROW)->equally()->bind(RptRow::Column::ROW)->
            where()->field(RptRow::Column::ID)->equally()->bind(RptRow::Column::ID)->
            prepare();

}

