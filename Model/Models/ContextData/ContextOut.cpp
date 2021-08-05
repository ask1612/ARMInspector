/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContextOut.cpp
 * Author: kazun_as
 * 
 * Created on 29 июля 2021 г., 12:08
 */

#include "ContextOut.h"
ModelWrapper::Model ContextOut::model_ = {ModelWrapper::Model::ContextOut};

ContextOut::ContextOut() {
}

ContextOut::~ContextOut() {
}
///Функции чтения - записи полей класса

void ContextOut::setRegnum(const QString& regnum) {
    regnum_ = regnum;
}

void ContextOut::setFio(const QString& fio) {
    fio_ = fio;
}

const QString& ContextOut::getRegnum()const {
    return regnum_;
}

const QString& ContextOut::getFio()const {
    return fio_;
}


///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void ContextOut::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Report::getFieldArray();
    array<QString, CONTEXTOUT_COLUMN> fld = ContextOut::getFields();

    this->setRegnum(jsonObj[fld[ContextOut::Column::REGNUM]].toString());
    this->setFio(jsonObj[fld[ContextOut::Column::FIO]].toString());
}
///Запись полей класса в JSON объкт. 

void ContextOut::write(QJsonObject &jsonObj) const {

    array<QString, CONTEXTOUT_COLUMN> fld = ContextOut::getFields();
    jsonObj[fld[ContextOut::Column::REGNUM]] = this->getRegnum();
    jsonObj[fld[ContextOut::Column::FIO]] = this->getFio();
}

