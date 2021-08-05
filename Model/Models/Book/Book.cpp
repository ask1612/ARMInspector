/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Book.cpp
 * Author: kazun_as
 * 
 * Created on 4 августа 2021 г., 12:29
 */

#include "Book.h"

Book::Book() {
}

Book::~Book() {
}

void Book::setId(const qint64& id) {
    id_ = id;
}

void Book::setDocDate(const QString& date) {
    doc_date_ = date;
}

void Book::setInspectorId(const qint64& inspector) {
    inspector_id_ = inspector;
}

void Book::setPrepareIns(const qint64& prepar_insp) {
    prepar_insp_ = prepar_insp;
}

void Book::setRegNum(const QString& regnum) {
    reg_num_ = regnum;
}

void Book::setRegDate(const QString& date) {
    reg_date_ = date;
}

void Book::setDocsType(const qint64& type) {
    doc_type_ = type;
}

void Book::setState(const qint64& state) {
    state_ = state;
}

const qint64& Book::getId() const {
    return id_;
}

const QString& Book::getDocDate() const {
    return doc_date_;
}

const qint64& Book::getInspectorId() const {
    return inspector_id_;
}

const qint64& Book::getPrepareIns()const {
    return prepar_insp_;
}

const QString& Book::getRegNum()const {
    return reg_num_;
}

const QString& Book::getRegDate() const {
    return reg_date_;
}

const qint64& Book::getDocsType() const {
    return doc_type_;
}

const qint64& Book::getState() const {
    return state_;
}
///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void Book::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Book::getFieldArray();
    array<QString, BOOK_COLUMN> fld = Book::getFields();

    this->setId(jsonObj[fld[Book::Column::ID]].toInt());
    this->setDocDate(jsonObj[fld[Book::Column::DOC_DATE]].toString());
    this->setInspectorId(jsonObj[fld[Book::Column::INSPECTOR_ID]].toInt());
    this->setPrepareIns(jsonObj[fld[Book::Column::PREPAR_INSP]].toInt());
    this->setRegNum(jsonObj[fld[Book::Column::REG_NUM]].toString());
    this->setRegDate(jsonObj[fld[Book::Column::REG_DATE]].toString());
    this->setDocsType(jsonObj[fld[Book::Column::DOC_TYPE]].toInt());
    this->setState(jsonObj[fld[Book::Column::STATE]].toInt());

}
///Запись полей класса в JSON объкт. 

void Book::write(QJsonObject &jsonObj) const {

    array<QString, BOOK_COLUMN> fld = Book::getFields();
    jsonObj[fld[Book::Column::ID]] = this->getId();
    jsonObj[fld[Book::Column::DOC_DATE]] = this->getDocDate();
    jsonObj[fld[Book::Column::INSPECTOR_ID]] = this->getInspectorId();
    jsonObj[fld[Book::Column::PREPAR_INSP]] = this->getPrepareIns();
    jsonObj[fld[Book::Column::REG_NUM]] = this->getRegNum();
    jsonObj[fld[Book::Column::REG_DATE]] = this->getRegDate();
    jsonObj[fld[Book::Column::DOC_TYPE]] = this->getDocsType();
    jsonObj[fld[Book::Column::STATE]] = this->getState();
}

///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Book::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "Book::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, BOOK_COLUMN> fld = Book::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Book::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Book::Column::ID], this->getId());
                    break;
                case Book::Column::DOC_DATE:
                    asSqlQuery->bindValue(":" + fld[Book::Column::DOC_DATE], this->getDocDate());
                    break;
                case Book::Column::INSPECTOR_ID:
                    asSqlQuery->bindValue(":" + fld[Book::Column::INSPECTOR_ID], this->getInspectorId());
                    break;
                case Book::Column::PREPAR_INSP:
                    asSqlQuery->bindValue(":" + fld[Book::Column::PREPAR_INSP], this->getPrepareIns());
                    break;
                case Book::Column::REG_NUM:
                    asSqlQuery->bindValue(":" + fld[Book::Column::REG_NUM], this->getRegNum());
                    break;
                case Book::Column::REG_DATE:
                    asSqlQuery->bindValue(":" + fld[Book::Column::REG_DATE], this->getRegDate());
                    break;
                case Book::Column::DOC_TYPE:
                    asSqlQuery->bindValue(":" + fld[Book::Column::DOC_TYPE], this->getDocsType());
                    break;
                case Book::Column::STATE:
                    asSqlQuery->bindValue(":" + fld[Book::Column::STATE], this->getState());
                    break;
                default:
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}
