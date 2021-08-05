/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InspectionViewView.cpp
 * Author: kazun_as
 * 
 * Created on 14 мая 2021 г., 14:44
 */

#include "InspectionView.h"

ModelWrapper::Model InspectionView::model_ = {ModelWrapper::Model::InspectionView};

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

InspectionView::InspectionView() {
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

InspectionView::~InspectionView() {
}
///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void InspectionView::setId(const qint64& id) {
    id_ = id;
};

void InspectionView::setName(const QString& name) {
    name_ = name;
};

void InspectionView::setMro(const QString& mro) {
    mro_ = mro;
};

const qint64& InspectionView::getId()const {
    return id_;
};

const QString& InspectionView::getName()const {
    return name_;
};

const QString& InspectionView::getMro()const {
    return mro_;
};

///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void InspectionView::read(const QJsonObject &jsonObj) {
    array<QString, INSPECTIONVIEW_COLUMN> fld = InspectionView::getFields();
    this->setId(jsonObj[fld[InspectionView::Column::ID]].toInt());
    this->setName(jsonObj[fld[InspectionView::Column::NAME]].toString());
    this->setMro(jsonObj[fld[InspectionView::Column::MRO]].toString());

};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void InspectionView::write(QJsonObject &jsonObj) const {
    array<QString, INSPECTIONVIEW_COLUMN> fld = InspectionView::getFields();
    jsonObj[fld[InspectionView::Column::ID]] = this->getId();
    jsonObj[fld[InspectionView::Column::NAME]] = this->getName();
    jsonObj[fld[InspectionView::Column::MRO]] = this->getMro();
};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant InspectionView::getData(const int& position) const {

    switch (position) {
        case InspectionView::Column::ID:
            return this->getId();
        case InspectionView::Column::NAME:
            return this->getName();
        case InspectionView::Column::MRO:
            return this->getMro();
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

void InspectionView::setData(const int& position, const QVariant& value) {
    switch (position) {
        case InspectionView::Column::ID:
            this->setId(value.toInt());
            break;
        case InspectionView::Column::NAME:
            this->setName(value.toString());
            break;
        case InspectionView::Column::MRO:
            this->setMro(value.toString());
            break;
        default:
            break;
    }

};


