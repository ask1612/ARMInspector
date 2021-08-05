/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Prepare.cpp
 * Author: kazun_as
 * 
 * Created on 4 августа 2021 г., 12:29
 */

#include "Prepare.h"

Prepare::Prepare() {
}

Prepare::~Prepare() {
}

const qint64& Prepare::getId() const {
    return id_;

}

const qint64& Prepare::getInspectorId() const {
    return inspector_id_;
}

const qint64& Prepare::getStatuteNum() const {
    return statute_num_;
}

const QString& Prepare::getStatuteDate() const {
    return statute_date_;
}

const QString& Prepare::getFioPenalized() const {
    return fio_penalized_;
}

const double& Prepare::getSumma() const {
    return summa_;
}

const qint64& Prepare::getProtocolNum() const {
    return protocol_num_;
}

const QString& Prepare::getProtocolDate() const {
    return protocol_date_;
}

const QString& Prepare::getProtocolFio() const {
    return protocol_fio_;
}

const qint64& Prepare::getNnsi10() const {
    return nsi_10_;
}

const qint64& Prepare::getDocNum() const {
    return doc_num_;
}

const QString& Prepare::getDocDate() const {
    return doc_date_;
}

const QString& Prepare::getAddressat() const {
    return addressat_;
}

const qint64& Prepare::getArticl7() const {
    return articl_7_;
}

const qint64& Prepare::getArticl5() const {
    return articl_5_;
}

const qint64& Prepare::getArticl51() const {
    return articl_51_;
}

const qint64& Prepare::getArticle() const {
    return article_;
}

const qint64& Prepare::getPunkt() const {
    return punkt_;
}

const qint64& Prepare::getDocId() const {
    return doc_id_;
}

void Prepare::setId(const qint64& id) {
    id_ = id;
}

void Prepare::setInspectorId(const qint64& inspector_id) {
    inspector_id_ = inspector_id;
}

void Prepare::setStatuteNum(const qint64& statute_num) {
    statute_num_ = statute_num;
}

void Prepare::setStatuteDate(const QString& statute_date) {
    statute_date_ = statute_date;
}

void Prepare::setFioPenalized(const QString& fio_penalized) {
    fio_penalized_ = fio_penalized;
}

void Prepare::setSumma(const double& summa) {
    summa_ = summa;
}

void Prepare::setProtocolNum(const qint64& protocol_num) {
    protocol_num_ = protocol_num;

}

void Prepare::setProtocolDate(const QString& protocol_date) {
    protocol_date_ = protocol_date;
}

void Prepare::setProtocolFio(const QString& protocol_fio) {
    protocol_fio_ = protocol_fio;
}

void Prepare::setNnsi10(const qint64& nsi_10) {
    nsi_10_ = nsi_10;
}

void Prepare::setDocNum(const qint64& doc_num) {
    doc_num_ = doc_num;
}

void Prepare::setDocDate(const QString& doc_date) {
    doc_date_ = doc_date;
}

void Prepare::setAddressat(const QString& addressat) {
    addressat_ = addressat;
}

void Prepare::setArticl7(const qint64& articl_7) {
    articl_7_ = articl_7;
}

void Prepare::setArticl5(const qint64& articl_5) {
    articl_5_ = articl_5;
}

void Prepare::setArticl51(const qint64& articl_51) {
    articl_51_ = articl_51;
}

void Prepare::setArticle(const qint64& article) {
    article_ = article;
}

void Prepare::setPunkt(const qint64& punkt) {
    punkt_ = punkt;
}

void Prepare::setDocId(const qint64& doc_id) {
    doc_id_ = doc_id;
}



///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void Prepare::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Prepare::getFieldArray();
    array<QString, PREPARE_COLUMN> fld = Prepare::getFields();

    this->setId(jsonObj[fld[Prepare::Column::ID]].toInt());
    this->setInspectorId(jsonObj[fld[Prepare::Column::INSPECTOR_ID]].toInt());
    this->setStatuteNum(jsonObj[fld[Prepare::Column::STATUTE_NUM]].toInt());
    this->setStatuteDate(jsonObj[fld[Prepare::Column::STATUTE_DATE]].toString());
    this->setFioPenalized(jsonObj[fld[Prepare::Column::FIO_PENALIZED]].toString());
    this->setSumma(jsonObj[fld[Prepare::Column::SUMMA]].toDouble());
    this->setProtocolNum(jsonObj[fld[Prepare::Column::PROTOCOL_NUM]].toInt());
    this->setProtocolDate(jsonObj[fld[Prepare::Column::PROTOCOL_DATE]].toString());
    this->setProtocolFio(jsonObj[fld[Prepare::Column::PROTOCOL_FIO]].toString());
    this->setNnsi10(jsonObj[fld[Prepare::Column::NSI_10]].toInt());
    this->setDocNum(jsonObj[fld[Prepare::Column::DOC_NUM]].toInt());
    this->setDocDate(jsonObj[fld[Prepare::Column::DOC_DATE]].toString());
    this->setAddressat(jsonObj[fld[Prepare::Column::ADDRESSAT]].toString());
    this->setArticl7(jsonObj[fld[Prepare::Column::ARTICL_7]].toInt());
    this->setArticl5(jsonObj[fld[Prepare::Column::ARTICL_5]].toInt());
    this->setArticl51(jsonObj[fld[Prepare::Column::ARTICL_51]].toInt());
    this->setArticle(jsonObj[fld[Prepare::Column::ARTICLE]].toInt());
    this->setPunkt(jsonObj[fld[Prepare::Column::PUNKT]].toInt());
    this->setDocId(jsonObj[fld[Prepare::Column::DOC_ID]].toInt());


}
///Запись полей класса в JSON объкт. 

void Prepare::write(QJsonObject &jsonObj) const {

    array<QString, PREPARE_COLUMN> fld = Prepare::getFields();


    jsonObj[fld[Prepare::Column::ID]] = this->getId();
    jsonObj[fld[Prepare::Column::INSPECTOR_ID]] = this->getInspectorId();
    jsonObj[fld[Prepare::Column::STATUTE_NUM]] = this->getStatuteNum();
    jsonObj[fld[Prepare::Column::STATUTE_DATE]] = this->getStatuteDate();
    jsonObj[fld[Prepare::Column::FIO_PENALIZED]] = this->getFioPenalized();
    jsonObj[fld[Prepare::Column::SUMMA]] = this->getSumma();
    jsonObj[fld[Prepare::Column::PROTOCOL_NUM]] = this->getProtocolNum();
    jsonObj[fld[Prepare::Column::PROTOCOL_DATE]] = this->getProtocolDate();
    jsonObj[fld[Prepare::Column::PROTOCOL_FIO]] = this->getProtocolFio();
    jsonObj[fld[Prepare::Column::NSI_10]] = this->getNnsi10();
    jsonObj[fld[Prepare::Column::DOC_NUM]] = this->getDocNum();
    jsonObj[fld[Prepare::Column::DOC_DATE]] = this->getDocDate();
    jsonObj[fld[Prepare::Column::DOC_DATE]] = this->getAddressat();
    jsonObj[fld[Prepare::Column::ARTICL_7]] = this->getArticl7();
    jsonObj[fld[Prepare::Column::ARTICL_5]] = this->getArticl5();
    jsonObj[fld[Prepare::Column::ARTICL_51]] = this->getArticl51();
    jsonObj[fld[Prepare::Column::ARTICLE]] = this->getArticle();
    jsonObj[fld[Prepare::Column::PUNKT]] = this->getPunkt();
    jsonObj[fld[Prepare::Column::DOC_ID]] = this->getDocId();
}
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Prepare::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "Prepare::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, PREPARE_COLUMN> fld = Prepare::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Prepare::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::ID], this->getId());
                    break;
                case Prepare::Column::INSPECTOR_ID:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::INSPECTOR_ID], this->getInspectorId());
                    break;
                case Prepare::Column::STATUTE_NUM:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::STATUTE_NUM], this->getStatuteNum());
                    break;
                case Prepare::Column::STATUTE_DATE:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::STATUTE_DATE], this->getStatuteDate());
                    break;
                case Prepare::Column::FIO_PENALIZED:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::FIO_PENALIZED], this->getFioPenalized());
                    break;
                case Prepare::Column::SUMMA:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::SUMMA], this->getSumma());
                    break;
                case Prepare::Column::PROTOCOL_NUM:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::PROTOCOL_NUM], this->getProtocolNum());
                    break;
                case Prepare::Column::PROTOCOL_DATE:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::PROTOCOL_DATE], this->getProtocolDate());
                    break;
                case Prepare::Column::PROTOCOL_FIO:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::PROTOCOL_FIO], this->getProtocolFio());
                    break;
                case Prepare::Column::NSI_10:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::NSI_10], this->getNnsi10());
                    break;
                case Prepare::Column::DOC_NUM:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::DOC_NUM], this->getDocNum());
                    break;
                case Prepare::Column::DOC_DATE:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::DOC_DATE], this->getDocDate());
                    break;
                case Prepare::Column::ADDRESSAT:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::DOC_DATE], this->getAddressat());
                    break;
                case Prepare::Column::ARTICL_7:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::ARTICL_7], this->getArticl7());
                    break;
                case Prepare::Column::ARTICL_5:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::ARTICL_5], this->getArticl5());
                    break;
                case Prepare::Column::ARTICL_51:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::ARTICL_51], this->getArticl51());
                    break;
                case Prepare::Column::ARTICLE:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::ARTICLE], this->getArticle());
                    break;
                case Prepare::Column::PUNKT:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::PUNKT], this->getPunkt());
                    break;
                case Prepare::Column::DOC_ID:
                    asSqlQuery->bindValue(":" + fld[Prepare::Column::DOC_ID], this->getDocId());
                    break;
                default:
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}
