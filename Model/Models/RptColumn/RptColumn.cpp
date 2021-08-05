/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumn.cpp
 * Author: kazun_as
 * 
 * Created on 23 апреля 2021 г., 15:14
 */

#include "RptColumn.h"
ModelWrapper::Model RptColumn::model_ = {ModelWrapper::Model::RptColumn};

RptColumn::RptColumn() {
}

RptColumn::~RptColumn() {
}

///-----------------------------------------------------------------------------
///
///         Функции записи-чтения полей класса.
///          
///-----------------------------------------------------------------------------

void RptColumn::setId(const qint64& id) {
    id_ = id;
};

void RptColumn::setArticle(const qint64& article) {
    article_ = article;
};

void RptColumn::setSubject(const qint64& offense_subject) {
    subject_ = offense_subject;
};

void RptColumn::setCol(const qint64& col) {
    col_ = col;
};

const qint64& RptColumn::getId() const {
    return id_;
};

const qint64& RptColumn::getArticle() const {
    return article_;
};

const qint64& RptColumn::getSubject() const {
    return subject_;
};

const qint64& RptColumn::getCol() const {
    return col_;
};



///-----------------------------------------------------------------------------
///
///         Считывание данных внешнего JSON объекта и 
///         запись их в соответствующие поля класса 
///         Используется при сериализации объекта класса        
///          
///-----------------------------------------------------------------------------

void RptColumn::read(const QJsonObject &jsonObj) {
    array<QString, RPT_COLUMN> fld = RptColumn::getFields();
    this->setId(jsonObj[fld[RptColumn::Column::ID]].toInt());
    this->setArticle(jsonObj[fld[RptColumn::Column::ARTICLE]].toInt());
    this->setSubject(jsonObj[fld[RptColumn::Column::SUBJECT]].toInt());
    this->setCol(jsonObj[fld[RptColumn::Column::COL]].toInt());
};

///-----------------------------------------------------------------------------
///
///         Запись данных полей класса во внешнний JSON объект. 
///         Используется при сериализации объекта класса         
///
///-----------------------------------------------------------------------------

void RptColumn::write(QJsonObject &jsonObj) const {
    array<QString, RPT_COLUMN> fld = RptColumn::getFields();

    jsonObj[fld[RptColumn::Column::ID]] = this->getId();
    jsonObj[fld[RptColumn::Column::ARTICLE]] = this->getArticle();
    jsonObj[fld[RptColumn::Column::SUBJECT]] = this->getSubject();
    jsonObj[fld[RptColumn::Column::COL]] = this->getCol();

};

///-----------------------------------------------------------------------------
///
///         Прочитать данные любого из полей класса. 
///         Используется при моделировании QAbstractTableModel         
///
///-----------------------------------------------------------------------------

const QVariant RptColumn::getData(const int& position) const {

    switch (position) {
        case RptColumn::Column::ID:
            return this->getId();
        case RptColumn::Column::ARTICLE:
            return this->getArticle();
        case RptColumn::Column::SUBJECT:
            return this->getSubject();
        case RptColumn::Column::COL:
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

void RptColumn::setData(const int& position, const QVariant& value) {
    switch (position) {
        case RptColumn::Column::ID:
            this->setId(value.toInt());
            break;
        case RptColumn::Column::ARTICLE:
            this->setArticle(value.toInt());
            break;
        case RptColumn::Column::SUBJECT:
            this->setSubject(value.toInt());
            break;
        case RptColumn::Column::COL:
            this->setCol(value.toInt());
            break;
        default:
            break;
    }

};

///-----------------------------------------------------------------------------
///
///
///         Привязать данные к запросу. 
///
///
///-----------------------------------------------------------------------------

void RptColumn::bindData(QSqlQuery* asSqlQuery) {
    //qInfo() << "RptColumn::bindData";
    QList<int> list = query_.getBindColumnList();
    if (!list.isEmpty()) {
        array<QString, RPT_COLUMN> fld = RptColumn::getFields();
        for (int i = 0; i < list.size(); i++) {
            //qInfo() << QString::number(list.at(i));
            switch (list.at(i)) {
                case RptColumn::Column::ID:
                    asSqlQuery->bindValue(":" + fld[RptColumn::Column::ID], this->getId());
                    break;
                case RptColumn::Column::ARTICLE:
                    asSqlQuery->bindValue(":" + fld[RptColumn::Column::ARTICLE], this->getArticle());
                    break;
                case RptColumn::Column::SUBJECT:
                    asSqlQuery->bindValue(":" + fld[RptColumn::Column::SUBJECT], this->getSubject());
                    break;
                case RptColumn::Column::COL:
                    asSqlQuery->bindValue(":" + fld[RptColumn::Column::COL], this->getCol());
                    break;
            }
        }
        //QMessageBox::information(0, "Information Box", this->getName());
    }
}

///-----------------------------------------------------------------------------
///
///         Добавить запись в справочник . 
///
///
///-----------------------------------------------------------------------------

const QString& RptColumn::insert() {
    //qInfo() << "RptColumn::insert()";
    return query_.insert()->field(RptColumn::Column::ARTICLE)->
            field(RptColumn::Column::SUBJECT)->
            field(RptColumn::Column::COL)->
            prepare();
}

///-----------------------------------------------------------------------------
///
///         Изменить данные инспекции. 
///
///
///-----------------------------------------------------------------------------

const QString& RptColumn::update() {
    //qInfo() << "RptColumn::update()";
    return query_.update()->set()->
            //            field(User::Column::ID)->equally()->bind(User::Column::ID)->
            field(RptColumn::Column::ARTICLE)->equally()->bind(RptColumn::Column::ARTICLE)->
            field(RptColumn::Column::SUBJECT)->equally()->bind(RptColumn::Column::SUBJECT)->
            field(RptColumn::Column::COL)->equally()->bind(RptColumn::Column::COL)->
            where()->field(RptColumn::Column::ID)->equally()->bind(RptColumn::Column::ID)->
            prepare();

}
