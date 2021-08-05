/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Msg.cpp
 * Author: kazun_as
 * 
 * Created on 4 августа 2021 г., 12:29
 */

#include "Msg.h"

Msg::Msg() {
}

Msg::~Msg() {
}

void Msg::setId(const qint64& id) {
    id_ = id;
}

void Msg::setNum(const QString& num) {
    num_ = num;

}

void Msg::setMsgDate(const QString& msg_date) {
    msg_date_ = msg_date;

}

void Msg::setNsi1(const qint64& nsi1) {
    nsi_1_ = nsi1;

}

void Msg::setToWho(const QString& to_who) {
    to_who_ = to_who;

}

void Msg::setDocId(const qint64& doc_id) {
    doc_id_ = doc_id;

}

const qint64& Msg::getId() const {
    return id_;
}

const QString& Msg::getNum() const {
    return num_;

}

const QString& Msg::getMsgDate() const {
    return msg_date_;

}

const qint64& Msg::getNsi1() const {
    return nsi_1_;

}

const QString& Msg::getToWho() const {
    return to_who_;

}

const qint64& Msg::getDocId() const {
    return doc_id_;

}

///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void Msg::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Msg::getFieldArray();
    array<QString, MSG_COLUMN> fld = Msg::getFields();

    this->setId(jsonObj[fld[Msg::Column::ID]].toInt());
    this->setNum(jsonObj[fld[Msg::Column::NUM]].toString());
    this->setMsgDate(jsonObj[fld[Msg::Column::MSG_DATE]].toString());
    this->setNsi1(jsonObj[fld[Msg::Column::NSI_1]].toInt());
    this->setToWho(jsonObj[fld[Msg::Column::TO_WHO]].toString());
    this->setDocId(jsonObj[fld[Msg::Column::DOC_ID]].toInt());

}
///Запись полей класса в JSON объкт. 

void Msg::write(QJsonObject &jsonObj) const {

    array<QString, MSG_COLUMN> fld = Msg::getFields();
    jsonObj[fld[Msg::Column::ID]] = this->getId();
    jsonObj[fld[Msg::Column::NUM]] = this->getNum();
    jsonObj[fld[Msg::Column::MSG_DATE]] = this->getMsgDate();
    jsonObj[fld[Msg::Column::NSI_1]] = this->getNsi1();
    jsonObj[fld[Msg::Column::TO_WHO]] = this->getToWho();
    jsonObj[fld[Msg::Column::DOC_ID]] = this->getDocId();
}
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Msg::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "Msg::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, MSG_COLUMN> fld = Msg::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Msg::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Msg::Column::ID], this->getId());
                    break;
                case Msg::Column::NUM:
                    asSqlQuery->bindValue(":" + fld[Msg::Column::NUM], this->getNum());
                    break;
                case Msg::Column::MSG_DATE:
                    asSqlQuery->bindValue(":" + fld[Msg::Column::MSG_DATE], this->getMsgDate());
                    break;
                case Msg::Column::NSI_1:
                    asSqlQuery->bindValue(":" + fld[Msg::Column::NSI_1], this->getNsi1());
                    break;
                case Msg::Column::TO_WHO:
                    asSqlQuery->bindValue(":" + fld[Msg::Column::TO_WHO], this->getToWho());
                    break;
                case Msg::Column::DOC_ID:
                    asSqlQuery->bindValue(":" + fld[Msg::Column::DOC_ID], this->getDocId());
                    break;
                default:
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}
