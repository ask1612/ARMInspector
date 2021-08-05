/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MQuery_IMPL.h
 * Author: kazun_as
 * 
 * Created on 28 апреля 2021 г., 10:14
 */
#ifndef MQUERY_IMPL_H
#define MQUERY_IMPL_H

#include "MQuery.h"



///-----------------------------------------------------------------------------
///
///             Получить список привязанных к запросу полей.
///
///-----------------------------------------------------------------------------

template <class T> const QList<int>& MQuery<T>::getBindColumnList() {
    return bind_;
}
///-----------------------------------------------------------------------------
///
///             Выбрать записи.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::select() {
    clear();
    QString asSelect = "SELECT * FROM " + T::getModelName();
    query_.append(asSelect);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Вызвать хранимую процедуру.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::call() {
    clear();
    QString asCall = "CALL " + T::getModelName();
    //query_.append(asCall);
    call_.append(asCall);
    return this;
}


///-----------------------------------------------------------------------------
///
///             Вставить запись.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::insert() {
    clear();
    QString asInsert = "INSERT INTO " + T::getModelName();
    insert_.append(asInsert);
    query_.append(asInsert);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Редактировать  запись.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::update() {
    clear();
    QString asUpdate = "UPDATE " + T::getModelName();
    query_.append(asUpdate);
    return this;
}

///-----------------------------------------------------------------------------
///
///             Запрос или значение параметра.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::strquery(const QString& asQuery) {
    query_.append(asQuery);
    return this;
}
///-----------------------------------------------------------------------------
///
///             удалить запись.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::remove() {
    clear();
    QString asDelete = "Delete   from " + T::getModelName();
    query_.append(asDelete);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Равно.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::equally() {
    QString asDelete = " = ";
    query_.append(asDelete);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Установить значения.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::set() {
    QString asSet = " set ";
    query_.append(asSet);
    return this;
}
///-----------------------------------------------------------------------------
///
///             Условие.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::where() {
    QString asWhere = " where ";
    query_.append(asWhere);
    where_.append(asWhere);
    return this;
}

///-----------------------------------------------------------------------------
///
///             Привязать поле модели.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::bind(const int& column) {
    query_.append(":" + T::getFields()[column]);
    bind_.append(column);
    return this;
}

///-----------------------------------------------------------------------------
///
///             Поле модели.
///
///-----------------------------------------------------------------------------

template <class T> MQuery<T>* MQuery<T>::field(const int& column) {
    field_.append(T::getFields()[column]);
    if (insert_.isEmpty() && call_.isEmpty()) {
        if (bind_.isEmpty()) {
            query_.append(" " + T::getFields()[column]);
        } else {
            if (where_.isEmpty()) {
                query_.append(", " + T::getFields()[column]);
            } else {
                query_.append(" " + T::getFields()[column]);
            }
        }
    } else if (!insert_.isEmpty()) {
        bind_.append(column);
    }
    return this;
}


///-----------------------------------------------------------------------------
///
///             Сгенерировать запрос.
///
///-----------------------------------------------------------------------------

template <class T> const QString& MQuery<T>::prepare() {
    queryStr_ = "";
    if (insert_.isEmpty() && call_.isEmpty()) {//
        for (int i = 0; i < query_.size(); i++) {
            queryStr_ += query_.at(i);
        };
    } else if (!insert_.isEmpty()) {//Это  INSERT
        for (int i = 0; i < insert_.size(); i++) {
            queryStr_ += insert_.at(i);
        };
        queryStr_ += " (";
        for (int i = 0; i < field_.size(); i++) {
            queryStr_ += field_.at(i);
            if (i < field_.size() - 1) {
                queryStr_ += ",";
            }
        };
        queryStr_ += ") ";
        queryStr_ += " VALUES (";
        for (int i = 0; i < field_.size(); i++) {
            queryStr_ += ":" + field_.at(i);
            if (i < field_.size() - 1) {
                queryStr_ += ",";
            }
        };
        queryStr_ += ") ";
    } else if (!call_.isEmpty()) {//Это CALL
        for (int i = 0; i < call_.size(); i++) {
            queryStr_ += call_.at(i);
        };
        queryStr_ += "(";
        for (int i = 0; i < field_.size(); i++) {
            queryStr_ += ":" + field_.at(i);
            if (i < field_.size() - 1) {
                queryStr_ += ",";
            }
        };
        queryStr_ += ") ";

    }
    return queryStr_;
}

///-----------------------------------------------------------------------------
///
///             Очистить списки.
///
///-----------------------------------------------------------------------------

template <class T> void MQuery<T>::clear() {
    query_.clear();
    bind_.clear();
    where_.clear();
    insert_.clear();
    field_.clear();
    call_.clear();
}


///-----------------------------------------------------------------------------
///
///             Выбрать все записи.
///
///-----------------------------------------------------------------------------

template <class T> QString MQuery<T>::selectAll() {
    return "SELECT * FROM " + T::getModelName();

}

///-----------------------------------------------------------------------------
///
///             Выбрать  запись по ID.
///
///-----------------------------------------------------------------------------

template <class T> QString MQuery<T>::selectById(const int& id) {

    return "SELECT * FROM " + T::getModelName() + " where id=" + QString::number(id);
}
///-----------------------------------------------------------------------------
///
///             Удалить  запись по ID.
///
///-----------------------------------------------------------------------------

template <class T> QString MQuery<T>::removeById(const int& id) {

    return "DELETE FROM " + T::getModelName() + " where id=" + QString::number(id);

}
///-----------------------------------------------------------------------------
///
///             Max  ID.
///
///-----------------------------------------------------------------------------

template <class T> QString MQuery<T>::selectMaxID() {

    return "SELECT * FROM " + T::getModelName() +
            " WHERE ID = (SELECT max(ID) FROM " +
            T::getModelName() + ")";
}


#endif /* MQUERY_IMPL_H */