/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Act.cpp
 * Author: kazun_as
 * 
 * Created on 4 августа 2021 г., 12:29
 */

#include "Act.h"

Act::Act() {
}

Act::~Act() {
}

void Act::setId(const qint64& id) {
    id_ = id;
}

void Act::setNum(const QString& num) {
    num_ = num;

}

void Act::setActDate(const QString& act_date) {
    act_date_ = act_date;

}

void Act::setNsi2(const qint64& nsi2) {
    nsi_2_ = nsi2;
}

void Act::setSumma(const double& summa) {
    summa_ = summa;
}

void Act::setTicketNum(const qint64& tnum) {
    ticket_num_ = tnum;
}

void Act::setTicketDate(const QString& tdate) {
    ticket_date_ = tdate;
}

void Act::setToWho(const QString& to_who) {
    to_who_ = to_who;

}

void Act::setDocId(const qint64& doc_id) {
    doc_id_ = doc_id;

}

const qint64& Act::getId() const{
    return id_;
}

const QString& Act::getNum() const {
    return num_;
}

const QString& Act::getActDate() const {
    return act_date_;

}

const qint64& Act::getNsi2() const {
    return nsi_2_;

}

const double& Act::getSumma() const {
    return summa_;

}

const QString& Act::getTicketDate() const {
    return ticket_date_;

}

const qint64& Act::getTicketNum() const {
    return ticket_num_;
}

const QString& Act::getToWho() const {
    return to_who_;

}

const qint64& Act::getDocId() const {
    return doc_id_;

}



///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void Act::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Act::getFieldArray();
    array<QString, ACT_COLUMN> fld = Act::getFields();

    this->setId(jsonObj[fld[Act::Column::ID]].toInt());
    this->setNum(jsonObj[fld[Act::Column::NUM]].toString());
    this->setActDate(jsonObj[fld[Act::Column::ACT_DATE]].toString());
    this->setNsi2(jsonObj[fld[Act::Column::NSI_2]].toInt());
    this->setSumma(jsonObj[fld[Act::Column::SUMMA]].toDouble());
    this->setTicketDate(jsonObj[fld[Act::Column::TICKET_DATE]].toString());
    this->setTicketNum(jsonObj[fld[Act::Column::TICKET_DATE]].toInt());
    this->setToWho(jsonObj[fld[Act::Column::TO_WHO]].toString());
    this->setDocId(jsonObj[fld[Act::Column::DOC_ID]].toInt());

}
///Запись полей класса в JSON объкт. 

void Act::write(QJsonObject &jsonObj) const {

    array<QString, ACT_COLUMN> fld = Act::getFields();

    jsonObj[fld[Act::Column::ID]] = this->getId();
    jsonObj[fld[Act::Column::NUM]] = this->getNum();
    jsonObj[fld[Act::Column::ACT_DATE]] = this->getActDate();
    jsonObj[fld[Act::Column::NSI_2]] = this->getNsi2();
    jsonObj[fld[Act::Column::SUMMA]] = this->getSumma();
    jsonObj[fld[Act::Column::TICKET_NUM]] = this->getTicketNum();
    jsonObj[fld[Act::Column::TICKET_DATE]] = this->getTicketDate();
    jsonObj[fld[Act::Column::TO_WHO]] = this->getToWho();
    jsonObj[fld[Act::Column::DOC_ID]] = this->getDocId();
}
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Act::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "Act::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, ACT_COLUMN> fld = Act::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Act::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Act::Column::ID], this->getId());
                    break;
                case Act::Column::NUM:
                    asSqlQuery->bindValue(":" + fld[Act::Column::NUM], this->getNum());
                    break;
                case Act::Column::ACT_DATE:
                    asSqlQuery->bindValue(":" + fld[Act::Column::ACT_DATE], this->getActDate());
                    break;
                case Act::Column::NSI_2:
                    asSqlQuery->bindValue(":" + fld[Act::Column::NSI_2], this->getNsi2());
                    break;
                case Act::Column::SUMMA:
                    asSqlQuery->bindValue(":" + fld[Act::Column::SUMMA], this->getSumma());
                    break;
                case Act::Column::TICKET_DATE:
                    asSqlQuery->bindValue(":" + fld[Act::Column::TICKET_DATE], this->getTicketDate());
                    break;
                case Act::Column::TICKET_NUM:
                    asSqlQuery->bindValue(":" + fld[Act::Column::TICKET_NUM], this->getTicketNum());
                    break;
                case Act::Column::TO_WHO:
                    asSqlQuery->bindValue(":" + fld[Act::Column::TO_WHO], this->getToWho());
                    break;
                case Act::Column::DOC_ID:
                    asSqlQuery->bindValue(":" + fld[Act::Column::DOC_ID], this->getDocId());
                    break;
                default:
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}
