/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 **
 **             Класс модели пользователя UserView.
 **             Используются для вывода данных о пользователе списком
 **
 ****************************************************************************/

/* 
 * File:   UserView.cpp
 * Author: kazun_as
 * 
 * Created on 5 апреля 2021 г., 10:41
 */

#include "User/UserView.h"
ModelWrapper::Model UserView::model_={ModelWrapper::Model::UserView};

///-----------------------------------------------------------------------------
///
///         Стандартный конструктор.
///          
///-----------------------------------------------------------------------------

UserView::UserView() {
}
///-----------------------------------------------------------------------------
///
///         Стандартный деструктор.
///          
///-----------------------------------------------------------------------------

UserView::~UserView() {
}
///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void UserView::setId(const qint64& id) {
    id_ = id;
};

void UserView::setFio(const QString& fio) {
    fio_ = fio;
};

void UserView::setInspection(const QString& inspection) {
    inspection_ = inspection;
};

void UserView::setName(const QString& name) {
    name_ = name;
};

const qint64& UserView::getId() const {
    return id_;
};

const QString& UserView::getFio() const {
    return fio_;
};

const QString& UserView::getInspection() const {
    return inspection_;
};

const QString& UserView::getName() const {
    return name_;
};
//-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void UserView::read(const QJsonObject &jsonObj) {
    this->setId(jsonObj["id"].toInt());
    this->setFio(jsonObj["fio"].toString());
    this->setInspection(jsonObj["name_i"].toString());
    this->setName(jsonObj["name"].toString());
};
///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void UserView::write(QJsonObject &jsonObj) const {

    jsonObj["id"] = this->getId();
    jsonObj["fio"] = this->getFio();
    jsonObj["name_i"] = this->getInspection();
    jsonObj["name"] = this->getName();

};
///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void UserView::setData(const int& position, const QVariant& value) {
    switch (position) {
        case 0:
            this->setId(value.toInt());
            break;
        case 1:
            this->setFio(value.toString());
            break;
        case 2:
            this->setInspection(value.toString());
            break;
        case 3:
            this->setName(value.toString());
            break;
        default:
            break;
    }

};
//-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant UserView::getData(const int& position) const {

    switch (position) {
        case 0:
            return this->getId();
        case 1:
            return this->getFio();
        case 2:
            return this->getInspection();
        case 3:
            return this->getName();
        default:
            return 0;
            break;
    }

};

