/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Penalty.cpp
 * Author: kazun_as
 * 
 * Created on 4 августа 2021 г., 12:29
 */

#include "Penalty.h"

Penalty::Penalty() {
}

Penalty::~Penalty() {
}

const qint64& Penalty::getId() const {
    return id_;

}

const qint64& Penalty::getNsi4() const {
    return nsi_4_;
}

const qint64& Penalty::getNsi11() const {
    return nsi_11_;
}

const qint64& Penalty::getStatuteNum() const {
    return statute_num_;
}

const QString& Penalty::getStatuteDate() const {
    return statute_date_;
}

const QString& Penalty::getForceDate() const {
    return force_date_;
}

const QString& Penalty::getFioPenalized() const {
    return fio_penalized_;
}

const qint64& Penalty::getNsi5() const {
    return nsi_5_;
}

const qint64& Penalty::getNsi6() const {
    return nsi_6_;
}

const qint64& Penalty::getNsi7() const {
    return nsi_7_;
}

const qint64& Penalty::getNsi8() const {
    return nsi_8_;
}

const double& Penalty::getSumma() const {
    return summa_;
}

const qint64& Penalty::getDocId() const {
    return doc_id_;
}

void Penalty::setId(const qint64& id) {
    id_ = id;
}

void Penalty::setNsi4(const qint64& nsi_4) {
    nsi_4_ = nsi_4;

}

void Penalty::setNsi11(const qint64& nsi_11) {
    nsi_11_ = nsi_11;
}

void Penalty::setStatuteNum(const qint64& statute_num) {
    statute_num_ = statute_num;
}

void Penalty::setStatuteDate(const QString& statute_date) {
    statute_date_ = statute_date;

}

void Penalty::setForceDate(const QString& force_date) {
    force_date_ = force_date;
}

void Penalty::setFioPenalized(const QString& fio_penalized) {
    fio_penalized_ = fio_penalized;
}

void Penalty::setNsi5(const qint64& nsi_5) {
    nsi_5_ = nsi_5;
}

void Penalty::setNsi6(const qint64& nsi_6) {
    nsi_6_ = nsi_6;
}

void Penalty::setNsi7(const qint64& nsi_7) {
    nsi_7_ = nsi_7;
}

void Penalty::setNsi8(const qint64& nsi_8) {
    nsi_8_ = nsi_8;
}

void Penalty::setSumma(const double& summa) {
    summa_ = summa;
}

void Penalty::setDocId(const qint64& doc_id) {
    doc_id_ = doc_id;
}



///Функции сериализации объекта класса
///Считывание JSON объкта в поля класса

void Penalty::read(const QJsonObject &jsonObj) {

    //array<QString, 10> fld_name=Penalty::Penalty::getFieldArray();
    array<QString, PENALTY_COLUMN> fld = Penalty::getFields();

    this->setId(jsonObj[fld[Penalty::Column::ID]].toInt());
    this->setNsi4(jsonObj[fld[Penalty::Column::NSI_4]].toInt());
    this->setNsi11(jsonObj[fld[Penalty::Column::NSI_11]].toInt());
    this->setStatuteNum(jsonObj[fld[Penalty::Column::STATUTE_NUM]].toInt());
    this->setStatuteDate(jsonObj[fld[Penalty::Column::STATUTE_DATE]].toString());
    this->setForceDate(jsonObj[fld[Penalty::Column::FORCE_DATE]].toString());
    this->setFioPenalized(jsonObj[fld[Penalty::Column::FIO_PENALIZED]].toString());
    this->setNsi5(jsonObj[fld[Penalty::Column::NSI_5]].toInt());
    this->setNsi6(jsonObj[fld[Penalty::Column::NSI_6]].toInt());
    this->setNsi7(jsonObj[fld[Penalty::Column::NSI_7]].toInt());
    this->setNsi8(jsonObj[fld[Penalty::Column::NSI_8]].toInt());
    this->setSumma(jsonObj[fld[Penalty::Column::SUMMA]].toDouble());
    this->setDocId(jsonObj[fld[Penalty::Column::DOC_ID]].toInt());



}
///Запись полей класса в JSON объкт. 

void Penalty::write(QJsonObject &jsonObj) const {

    array<QString, PENALTY_COLUMN> fld = Penalty::getFields();


    jsonObj[fld[Penalty::Column::ID]] = this->getId();
    jsonObj[fld[Penalty::Column::NSI_4]] = this->getNsi4();
    jsonObj[fld[Penalty::Column::NSI_11]] = this->getNsi11();
    jsonObj[fld[Penalty::Column::STATUTE_NUM]] = this->getStatuteNum();
    jsonObj[fld[Penalty::Column::STATUTE_DATE]] = this->getStatuteDate();
    jsonObj[fld[Penalty::Column::FORCE_DATE]] = this->getForceDate();
    jsonObj[fld[Penalty::Column::FIO_PENALIZED]] = this->getFioPenalized();
    jsonObj[fld[Penalty::Column::NSI_5]] = this->getNsi5();
    jsonObj[fld[Penalty::Column::NSI_6]] = this->getNsi6();
    jsonObj[fld[Penalty::Column::NSI_7]] = this->getNsi7();
    jsonObj[fld[Penalty::Column::NSI_8]] = this->getNsi8();
    jsonObj[fld[Penalty::Column::SUMMA]] = this->getSumma();
    jsonObj[fld[Penalty::Column::DOC_ID]] = this->getDocId();
}
///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void Penalty::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "Penalty::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, PENALTY_COLUMN> fld = Penalty::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case Penalty::Column::ID:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::ID], this->getId());
                    break;
                case Penalty::Column::NSI_4:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::NSI_4], this->getNsi4());
                    break;
                case Penalty::Column::NSI_11:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::NSI_11], this->getNsi11());
                    break;
                case Penalty::Column::STATUTE_NUM:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::STATUTE_NUM], this->getStatuteNum());
                    break;
                case Penalty::Column::STATUTE_DATE:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::STATUTE_DATE], this->getStatuteDate());
                    break;
                case Penalty::Column::FORCE_DATE:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::FORCE_DATE], this->getForceDate());
                    break;
                case Penalty::Column::FIO_PENALIZED:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::FIO_PENALIZED], this->getFioPenalized());
                    break;
                case Penalty::Column::NSI_5:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::NSI_5], this->getNsi5());
                    break;
                case Penalty::Column::NSI_6:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::NSI_6], this->getNsi6());
                    break;
                case Penalty::Column::NSI_7:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::NSI_7], this->getNsi7());
                    break;
                case Penalty::Column::NSI_8:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::NSI_8], this->getNsi8());
                    break;
                case Penalty::Column::SUMMA:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::SUMMA], this->getSumma());
                    break;
                case Penalty::Column::DOC_ID:
                    asSqlQuery->bindValue(":" + fld[Penalty::Column::DOC_ID], this->getDocId());
                    break;
                default:
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}
