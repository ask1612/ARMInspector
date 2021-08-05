/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Report.cpp
 * Author: kazun_as
 * 
 * Created on 19 мая 2021 г., 15:58
 */

#include "Report.h"
ModelWrapper::Model Report::model_ = {ModelWrapper::Model::Report};

Report::Report() {
}

Report::~Report() {
}

///Функции чтения - записи полей класса

void Report::setMro(const qint64& mro) {
    mro_ = mro;
}

void Report::setMon(const qint64& mon) {
    mon_ = mon;
}


void Report::setYear(const qint64& year) {
    year_ = year;
}

void Report::setNumrow(const qint64& numrow) {
    numrow_ = numrow;
}

void Report::setCummulative(const qint64& cummulative) {
    cummulative_ = cummulative;
}

const qint64& Report::getMro()const {
    return mro_;
}

const qint64& Report::getMon()const {
    return mon_;

}

const qint64& Report::getYear()const {
    return year_;

}

const qint64& Report::getNumrow()const {
    return numrow_;

}

const qint64& Report::getCummulative()const {
    return cummulative_;

}


///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void Report::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Report::getFieldArray();
    array<QString, REPORT_COLUMN> fld = Report::getFields();

    this->setMro(jsonObj[fld[Report::Column::MRO]].toInt());
    this->setMon(jsonObj[fld[Report::Column::MON]].toInt());
    this->setYear(jsonObj[fld[Report::Column::YEAR]].toInt());
    this->setNumrow(jsonObj[fld[Report::Column::NUMROW]].toInt());
    this->setCummulative(jsonObj[fld[Report::Column::CUMMULATIVE]].toInt());

}
///Запись полей класса в JSON объкт. 

void Report::write(QJsonObject &jsonObj) const {

    array<QString, REPORT_COLUMN> fld = Report::getFields();
    jsonObj[fld[Report::Column::MRO]] = this->getMro();
    jsonObj[fld[Report::Column::MON]] = this->getMon();
    jsonObj[fld[Report::Column::YEAR]] = this->getYear();
    jsonObj[fld[Report::Column::NUMROW]] = this->getNumrow();
    jsonObj[fld[Report::Column::CUMMULATIVE]] = this->getCummulative();
}
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Report::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "Report::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, REPORT_COLUMN> fld = Report::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Report::Column::MRO:
                    asSqlQuery->bindValue(":" + fld[Report::Column::MRO], this->getMro());
                    break;
                case Report::Column::MON:
                    asSqlQuery->bindValue(":" + fld[Report::Column::MON], this->getMon());
                    break;
                case Report::Column::YEAR:
                    asSqlQuery->bindValue(":" + fld[Report::Column::YEAR], this->getYear());
                    break;
                case Report::Column::NUMROW:
                    asSqlQuery->bindValue(":" + fld[Report::Column::NUMROW], this->getNumrow());
                    break;
                case Report::Column::CUMMULATIVE:
                    asSqlQuery->bindValue(":" + fld[Report::Column::CUMMULATIVE], this->getCummulative());
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

const QString& Report::call() {
    //qInfo() << "Report::call()";
    return query_.call()->
            field(Report::Column::MRO)->bind(Report::Column::MRO)->
            field(Report::Column::MON)->bind(Report::Column::MON)->
            field(Report::Column::YEAR)->bind(Report::Column::YEAR)->
            field(Report::Column::NUMROW)->bind(Report::Column::NUMROW)->
            field(Report::Column::CUMMULATIVE)->bind(Report::Column::CUMMULATIVE)->
            prepare();

}
