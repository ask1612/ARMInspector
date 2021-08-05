/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/****************************************************************************
 **
 **             Класс списка моделей ModelList.
 **             Исполъзуется для выводв списка моделей
 **             на экран  в виде таблицы     
 **
 ****************************************************************************/

/* 
 * File:   ModelList.h
 * Author: kazun_as
 *
 * Created on 29 марта 2021 г., 11:28
 */

#ifndef MODELLIST_H
#define MODELLIST_H
#include <QAbstractTableModel>
#include <QVariant>
#include <QList>
#include <QModelIndex>
#include <QJsonArray>

template <class T>
class ModelList : public QAbstractTableModel {
public:
    ///Констуктор
    ModelList();
    ModelList(QList<T> list);
    ///Деструктор

    virtual ~ModelList() {
    };

    ///Инициалировать список моделей
    void setListModel(const QList<T>& models);

    ///Количество колонок
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    ///Количество строк
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    ///Данные, отображаемые в каждой ячейке таблицы  
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    ///Названия колонок(или строк))
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    ///Добавить экземпляр модели в список
    void addModel(T& model);
    ///Удалить экземпляр модели из  списка
    void delModel(const QModelIndex & index);
    ///Получить модель из списка
    T getModel(const QModelIndex & index) const;
    
    
private:
    ///список моделей
    QList<T> m_ListModels;
    QVariant getData(int num, int position) const;
};
#include "ModelList_IMPL.h"
#endif /* MODELLIST_H */

