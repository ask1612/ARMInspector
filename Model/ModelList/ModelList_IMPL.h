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
 * File:   MosdelList_IMPL.h
 * Author: kazun_as
 *
 * Created on 29 марта 2021 г., 11:56
 */

#ifndef MOSDELLIST_IMPL_H
#define MOSDELLIST_IMPL_H
#include <QMessageBox>
#include "ModelList.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

template <class T> ModelList<T>::ModelList() {
}

///-----------------------------------------------------------------------------
///
///         Конструктор.
///         Инициализирует списк моделей
///          
///-----------------------------------------------------------------------------

template <class T> ModelList<T>::ModelList(QList<T> list) {
    m_ListModels = list;
}

///-----------------------------------------------------------------------------
///
///         Инициализировать списк моделей
///          
///-----------------------------------------------------------------------------

template <class T> void ModelList<T>::setListModel(const QList<T>& models) {
    m_ListModels = models;
}

///-----------------------------------------------------------------------------
///
///         Данные, отображаемые в каждой ячейке таблицы
///          
///-----------------------------------------------------------------------------

template <class T> QVariant ModelList<T>::data(const QModelIndex& index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole)
        return getData(index.row(), index.column());
    return QVariant();
}

///-----------------------------------------------------------------------------
///
///         Количество колонок
///          
///-----------------------------------------------------------------------------

template <class T> int ModelList<T>::columnCount(const QModelIndex & parent) const {
    //T model;
    QJsonArray arr = T::getColumnArray();
    return arr.size();
}

///-----------------------------------------------------------------------------
///
///         Количество строк
///          
///-----------------------------------------------------------------------------

template <class T> int ModelList<T>::rowCount(const QModelIndex& parent) const {
    return m_ListModels.size();
}

///-----------------------------------------------------------------------------
///
///         Данные определенного параметра  модели
///          
///-----------------------------------------------------------------------------

template <class T> QVariant ModelList<T>::getData(int num, int position) const {
    T model = m_ListModels.at(num);
    return model.getData(position);
}

///-----------------------------------------------------------------------------
///
///         Названия колонок(или строк))
///          
///-----------------------------------------------------------------------------

template <class T> QVariant ModelList<T>::headerData(int section, Qt::Orientation orientation, int role) const {
    // QMessageBox::information(0, "Information Box",m_pModel->getModelName());
    QJsonArray arr = T::getColumnArray();

    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Vertical)
        return QVariant(section + 1);
    else return QVariant(arr[section]);
}
///-----------------------------------------------------------------------------
///
///         Установить данные определенного экземпляра модели и определенного
///         её поля (на экране это - ячейка таблицы) 
///          
///-----------------------------------------------------------------------------

template <class T> bool ModelList<T>::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole) {
        T model = this->getModel(index);
        model.setData(index.column(), value);
        m_ListModels.replace(index.row(), model);
        //setValue(index.row(), index.column(), value.toString());
    }
    return false;
}
///-----------------------------------------------------------------------------
///
///         ItemFlags
///          
///          
///-----------------------------------------------------------------------------

template <class T> Qt::ItemFlags ModelList<T>::flags(const QModelIndex & /*index*/) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


///-----------------------------------------------------------------------------
///
///         Получить модель из списка
///          
///          
///-----------------------------------------------------------------------------

template <class T> T ModelList<T>::getModel(const QModelIndex & index) const {
    return m_ListModels.at(index.row());
    //return (*QList<T>)[index.row()];
}

///-----------------------------------------------------------------------------
///
///         добавить новую модель в список
///          
///          
///-----------------------------------------------------------------------------

template <class T> void ModelList<T>::addModel(T& model) {
    beginInsertRows(QModelIndex(), m_ListModels.size(), m_ListModels.size());
    m_ListModels.append(model);
    endInsertRows();
}
///-----------------------------------------------------------------------------
///
///         удалить модель из  списка
///          
///-----------------------------------------------------------------------------

template <class T> void ModelList<T>::delModel(const QModelIndex & index) {
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_ListModels.removeAt(index.row());
    endRemoveRows();
}



#endif /* MOSDELLIST_IMPL_H */

