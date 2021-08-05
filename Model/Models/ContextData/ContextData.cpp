/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContextData.cpp
 * Author: kazun_as
 * 
 * Created on 29 июля 2021 г., 11:39
 */

#include "ContextData.h"
ModelWrapper::Model ContextData::model_ = {ModelWrapper::Model::ContextData};

ContextData::ContextData() {
}
ContextData::~ContextData() {
}

///Функции чтения - записи полей класса

void ContextData::setMro(const qint64& mro) {
    mro_ = mro;
}

void ContextData::setMon(const qint64& mon) {
    mon_ = mon;
}


void ContextData::setYear(const qint64& year) {
    year_ = year;
}

void ContextData::setNumrow(const qint64& numrow) {
    numrow_ = numrow;
}
void ContextData::setNumcol(const qint64& numcol) {
    numcol_ = numcol;
}

void ContextData::setCummulative(const qint64& cummulative) {
    cummulative_ = cummulative;
}

const qint64& ContextData::getMro()const {
    return mro_;
}

const qint64& ContextData::getMon()const {
    return mon_;

}

const qint64& ContextData::getYear()const {
    return year_;

}

const qint64& ContextData::getNumrow()const {
    return numrow_;

}

const qint64& ContextData::getNumcol()const {
    return numcol_;

}

const qint64& ContextData::getCummulative()const {
    return cummulative_;

}


///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void ContextData::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=ContextData::getFieldArray();
    array<QString, CONTEXTDATA_COLUMN> fld = ContextData::getFields();

    this->setMro(jsonObj[fld[ContextData::Column::MRO]].toInt());
    this->setMon(jsonObj[fld[ContextData::Column::MON]].toInt());
    this->setYear(jsonObj[fld[ContextData::Column::YEAR]].toInt());
    this->setNumrow(jsonObj[fld[ContextData::Column::NUMROW]].toInt());
    this->setNumcol(jsonObj[fld[ContextData::Column::NUMCOL]].toInt());
    this->setCummulative(jsonObj[fld[ContextData::Column::CUMMULATIVE]].toInt());

}
///Запись полей класса в JSON объкт. 

void ContextData::write(QJsonObject &jsonObj) const {

    array<QString, CONTEXTDATA_COLUMN> fld = ContextData::getFields();
    jsonObj[fld[ContextData::Column::MRO]] = this->getMro();
    jsonObj[fld[ContextData::Column::MON]] = this->getMon();
    jsonObj[fld[ContextData::Column::YEAR]] = this->getYear();
    jsonObj[fld[ContextData::Column::NUMROW]] = this->getNumrow();
    jsonObj[fld[ContextData::Column::NUMCOL]] = this->getNumcol();
    jsonObj[fld[ContextData::Column::CUMMULATIVE]] = this->getCummulative();
}
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void ContextData::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "ContextData::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, CONTEXTDATA_COLUMN> fld = ContextData::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case ContextData::Column::MRO:
                    asSqlQuery->bindValue(":" + fld[ContextData::Column::MRO], this->getMro());
                    break;
                case ContextData::Column::MON:
                    asSqlQuery->bindValue(":" + fld[ContextData::Column::MON], this->getMon());
                    break;
                case ContextData::Column::YEAR:
                    asSqlQuery->bindValue(":" + fld[ContextData::Column::YEAR], this->getYear());
                    break;
                case ContextData::Column::NUMROW:
                    asSqlQuery->bindValue(":" + fld[ContextData::Column::NUMROW], this->getNumrow());
                    break;
                case ContextData::Column::NUMCOL:
                    asSqlQuery->bindValue(":" + fld[ContextData::Column::NUMCOL], this->getNumcol());
                    break;
                case ContextData::Column::CUMMULATIVE:
                    asSqlQuery->bindValue(":" + fld[ContextData::Column::CUMMULATIVE], this->getCummulative());
                    break;
                default:
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}
///-----------------------------------------------------------------------------
///
///         Вызвать хранимую процудуру. 
///
///-----------------------------------------------------------------------------

const QString& ContextData::call() {
    //qInfo() << "ContextData::call()";
    return  query_.call()->
            field(ContextData::Column::MRO)->bind(ContextData::Column::MRO)->
            field(ContextData::Column::MON)->bind(ContextData::Column::MON)->
            field(ContextData::Column::YEAR)->bind(ContextData::Column::YEAR)->
            field(ContextData::Column::NUMROW)->bind(ContextData::Column::NUMROW)->
            field(ContextData::Column::NUMCOL)->bind(ContextData::Column::NUMCOL)->
            field(ContextData::Column::CUMMULATIVE)->bind(ContextData::Column::CUMMULATIVE)->
            prepare();
}