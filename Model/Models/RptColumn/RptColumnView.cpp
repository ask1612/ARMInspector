/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumnViewView.cpp
 * Author: kazun_as
 * 
 * Created on 15 мая 2021 г., 13:49
 */

#include "RptColumnView.h"
ModelWrapper::Model RptColumnView::model_ = {ModelWrapper::Model::RptColumnView};
///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

RptColumnView::RptColumnView() {
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------
RptColumnView::~RptColumnView() {
}

///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void RptColumnView::setId(const qint64& id) {
    id_ = id;
};

void RptColumnView::setArticle(const QString& article) {
    article_ = article;
};

void RptColumnView::setSubject(const QString& subject) {
    subject_ = subject;
};

void RptColumnView::setCol(const qint64& col) {
    col_ = col;
};

const qint64& RptColumnView::getId() const {
    return id_;
};

const QString& RptColumnView::getArticle() const {
    return article_;
};

const QString& RptColumnView::getSubject() const {
    return subject_;
};

const qint64& RptColumnView::getCol() const {
    return col_;
};


///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void RptColumnView::read(const QJsonObject &jsonObj) {
    array<QString, RPTVIEW_COLUMN> fld = RptColumnView::getFields();
    this->setId(jsonObj[fld[RptColumnView::Column::ID]].toInt());
    this->setArticle(jsonObj[fld[RptColumnView::Column::ARTICLE]].toString());
    this->setSubject(jsonObj[fld[RptColumnView::Column::SUBJECT]].toString());
    this->setCol(jsonObj[fld[RptColumnView::Column::COL]].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void RptColumnView::write(QJsonObject &jsonObj) const {
    array<QString, RPTVIEW_COLUMN> fld = RptColumnView::getFields();

    jsonObj[fld[RptColumnView::Column::ID]] = this->getId();
    jsonObj[fld[RptColumnView::Column::ARTICLE]] = this->getArticle();
    jsonObj[fld[RptColumnView::Column::SUBJECT]] = this->getSubject();
    jsonObj[fld[RptColumnView::Column::COL]] = this->getCol();

};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant RptColumnView::getData(const int& position) const {

    switch (position) {
        case RptColumnView::Column::ID:
            return this->getId();
        case RptColumnView::Column::ARTICLE:
            return this->getArticle();
        case RptColumnView::Column::SUBJECT:
            return this->getSubject();
        case RptColumnView::Column::COL:
            return this->getCol();
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

void RptColumnView::setData(const int& position, const QVariant& value) {
    switch (position) {
        case RptColumnView::Column::ID:
            this->setId(value.toInt());
            break;
        case RptColumnView::Column::ARTICLE:
            this->setArticle(value.toString());
            break;
        case RptColumnView::Column::SUBJECT:
            this->setSubject(value.toString());
            break;
        case RptColumnView::Column::COL:
            this->setCol(value.toInt());
            break;
        default:
            break;
    }

};

