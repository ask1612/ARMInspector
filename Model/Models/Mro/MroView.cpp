/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MroViewView.cpp
 * Author: kazun
 * 
 * Created on 13 мая 2021 г., 20:11
 */

#include "MroView.h"
ModelWrapper::Model MroView::model_ = {ModelWrapper::Model::MroView};

MroView::MroView() : id_(0), name_(""), inspection_("") {
}

MroView::~MroView() {
}

void MroView::setId(const qint64& id) {
    id_ = id;
};

void MroView::setName(const QString& name) {
    name_ = name;
};

void MroView::setInspection(const QString& inspection) {
    inspection_ = inspection;
};

const qint64& MroView::getId() const {
    return id_;
};

const QString& MroView::getName() const {
    return name_;
};

const QString& MroView::getInspection() const {
    return inspection_;
};

///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void MroView::read(const QJsonObject &jsonObj) {

    array<QString, MROVIEW_COLUMN> fld = MroView::getFields();
    this->setId(jsonObj[fld[MroView::Column::ID]].toInt());
    this->setName(jsonObj[fld[MroView::Column::NAME]].toString());
    this->setInspection(jsonObj[fld[MroView::Column::INSPECTION]].toString());
    ///qDebug() << fld[MroView::Column::ID];
    ///qDebug() << fld[MroView::Column::NAME];
    ///qDebug() << fld[MroView::Column::INSPECTION];
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void MroView::write(QJsonObject &jsonObj) const {

    array<QString, MROVIEW_COLUMN> fld = MroView::getFields();
    jsonObj[fld[MroView::Column::ID]] = this->getId();
    jsonObj[fld[MroView::Column::NAME]] = this->getName();
    jsonObj[fld[MroView::Column::INSPECTION]] = this->getInspection();

};


///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant MroView::getData(const int& position) const {

    switch (position) {
        case MroView::Column::ID:
            return this->getId();
        case MroView::Column::NAME:
            return this->getName();
        case MroView::Column::INSPECTION:
            return this->getInspection();
        default:
            return 0;
            break;
    }
};

///-----------------------------------------------------------------------------
///
///         Записать  данные в любое з поле класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

void MroView::setData(const int& position, const QVariant& value) {
    switch (position) {
        case MroView::Column::ID:
            this->setId(value.toInt());
            break;
        case MroView::Column::NAME:
            this->setName(value.toString());
            break;
        case MroView::Column::INSPECTION:
            this->setInspection(value.toString());
            break;
        default:
            break;
    }

};



