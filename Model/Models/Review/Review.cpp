/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Review.cpp
 * Author: kazun_as
 * 
 * Created on 4 августа 2021 г., 12:29
 */

#include "Review.h"

Review::Review() {
}

Review::~Review() {
}

const qint64& Review::getId() const {
    return id_;

}


const qint64& Review::getNum() const {
    return num_;
}

const QString& Review::getViewDate() const {
    return view_date_;
}


const qint64& Review::getNsi11() const {
    return nsi_11_;
}

const qint64& Review::getInNum() const {
    return in_num_;
}

const QString& Review::getInDate() const {
    return in_date_;
}


const qint64& Review::getDocId() const {
    return doc_id_;
}

void Review::setId(const qint64& id) {
    id_ = id;
}


void Review::setNum(const qint64& num) {
    num_ = num;
}

void Review::setViewDate(const QString& date) {
    view_date_ = date;
}


void Review::setNsi11(const qint64& nsi_11) {
    nsi_11_ = nsi_11;
}

void Review::setInNum(const qint64& in_num) {
    in_num_ = in_num;
}

void Review::setInDate(const QString& in_date) {
    in_date_ = in_date;
}

void Review::setDocId(const qint64& doc_id) {
    doc_id_ = doc_id;
}



///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void Review::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Review::getFieldArray();
    array<QString, REVIEW_COLUMN> fld = Review::getFields();

    this->setId(jsonObj[fld[Review::Column::ID]].toInt());
    this->setNum(jsonObj[fld[Review::Column::NUM]].toInt());
    this->setViewDate(jsonObj[fld[Review::Column::VIEW_DATE]].toString());
    this->setNsi11(jsonObj[fld[Review::Column::NSI_11]].toInt());
    this->setInNum(jsonObj[fld[Review::Column::IN_NUM]].toInt());
    this->setInDate(jsonObj[fld[Review::Column::IN_DATE]].toString());
    this->setDocId(jsonObj[fld[Review::Column::DOC_ID]].toInt());


}
///Запись полей класса в JSON объкт. 

void Review::write(QJsonObject &jsonObj) const {

    array<QString, REVIEW_COLUMN> fld = Review::getFields();


    jsonObj[fld[Review::Column::ID]] = this->getId();
    jsonObj[fld[Review::Column::NUM]] = this->getNum();
    jsonObj[fld[Review::Column::VIEW_DATE]] = this->getViewDate();
    jsonObj[fld[Review::Column::NSI_11]] = this->getNsi11();
    jsonObj[fld[Review::Column::IN_NUM]] = this->getInNum();
    jsonObj[fld[Review::Column::IN_DATE]] = this->getInDate();
    jsonObj[fld[Review::Column::DOC_ID]] = this->getDocId();
}
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Review::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "Review::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, REVIEW_COLUMN> fld = Review::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Review::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Review::Column::ID], this->getId());
                    break;
                case Review::Column::NUM:
                    asSqlQuery->bindValue(":" + fld[Review::Column::NUM], this->getNum());
                    break;
                case Review::Column::VIEW_DATE:
                    asSqlQuery->bindValue(":" + fld[Review::Column::VIEW_DATE], this->getViewDate());
                    break;
                case Review::Column::NSI_11:
                    asSqlQuery->bindValue(":" + fld[Review::Column::NSI_11], this->getNsi11());
                    break;
                case Review::Column::IN_NUM:
                    asSqlQuery->bindValue(":" + fld[Review::Column::IN_NUM], this->getInNum());
                    break;
                case Review::Column::IN_DATE:
                    asSqlQuery->bindValue(":" + fld[Review::Column::IN_DATE], this->getInDate());
                    break;
                case Review::Column::DOC_ID:
                    asSqlQuery->bindValue(":" + fld[Review::Column::DOC_ID], this->getDocId());
                    break;
                default:
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}
