/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReportOut.cpp
 * Author: kazun_as
 * 
 * Created on 20 мая 2021 г., 09:22
 */

#include "ReportOut.h"

ReportOut::ReportOut() {
}
ReportOut::~ReportOut() {
}

///Функции чтения - записи полей класса

void ReportOut::setCol(const qint64& mycol) {
    mycol_ = mycol;
}

void ReportOut::setArticle(const qint64& article) {
    article_ = article;
}
void ReportOut::setMysubject(const qint64& mysubject) {
    mysubject_ = mysubject;
}
void ReportOut::setCount(const double& count) {
    count_ = count;
}


const qint64& ReportOut::getCol()const {
    return mycol_;
}

const qint64& ReportOut::getArticle()const {
    return article_;
}
const qint64& ReportOut::getMysubject()const {
    return mysubject_;
}
const double& ReportOut::getCount()const {
    return count_;
}

///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void ReportOut::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Report::getFieldArray();
    array<QString, OUT_COLUMN> fld = ReportOut::getFields();

    this->setCol(jsonObj[fld[ReportOut::Column::COL]].toInt());
    this->setArticle(jsonObj[fld[ReportOut::Column::ARTICLE]].toInt());
    this->setMysubject(jsonObj[fld[ReportOut::Column::MYSUBJECT]].toInt());
    this->setCount(jsonObj[fld[ReportOut::Column::COUNT]].toDouble());
}
///Запись полей класса в JSON объкт. 

void ReportOut::write(QJsonObject &jsonObj) const {

    array<QString, OUT_COLUMN> fld = ReportOut::getFields();
    jsonObj[fld[ReportOut::Column::COL]] = this->getCol();
    jsonObj[fld[ReportOut::Column::ARTICLE]] = this->getArticle();
    jsonObj[fld[ReportOut::Column::MYSUBJECT]] = this->getMysubject();
    jsonObj[fld[ReportOut::Column::COUNT]] = this->getCount();
}
