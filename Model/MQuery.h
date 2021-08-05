/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MQuery.h
 * Author: kazun_as
 *
 * Created on 28 апреля 2021 г., 10:14
 */

#ifndef MQUERY_H
#define MQUERY_H
#include <QtCore>

template <class T> class MQuery {
public:
    MQuery<T>* select();
    MQuery<T>* call();
    MQuery<T>* strquery(const QString&);
    MQuery<T>* insert();
    MQuery<T>* update();
    MQuery<T>* remove();
    MQuery<T>* where();
    MQuery<T>* set();
    MQuery<T>* field(const int&);
    MQuery<T>* equally();
    MQuery<T>* bind(const int&);
    MQuery<T>* bindprm(const QString&);
    const QString& prepare();
    void clear();
    const QList<int>& getBindColumnList();
    static QString selectAll();
    static QString selectMaxID();
    static QString selectById(const int&);
    static QString removeById(const int&);
private:
    /// Список объектов класса T. 
    QString queryStr_;
    QList<QString> query_;
    QList<int> bind_;
    QList<QString> where_;
    QList<QString> insert_;
    QList<QString> field_;
    QList<QString> call_;
    T* model_;
};
#include "MQuery_IMPL.h"
#endif /* MQUERY_H */

