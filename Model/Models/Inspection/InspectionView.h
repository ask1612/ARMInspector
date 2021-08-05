/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InspectionView.h
 * Author: kazun_as
 *
 * Created on 14 мая 2021 г., 14:44
 */

#ifndef INSPECTIONVIEW_H
#define INSPECTIONVIEW_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include "Model.h"
#include <QVariant>
#include <QJsonArray>
#include <array>
#include <MQuery.h>
#include "ModelWrapper.h"
#define INSPECTIONVIEW_COLUMN 3
using namespace std;

class InspectionView: public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NAME,
        MRO
    };
    ///Конструктор
    InspectionView();
    ///деструктор
    virtual ~InspectionView();
    ///Функции чтения - записи полей класса
    void setId(const qint64& id);
    void setName(const QString& name);
    void setMro(const QString& mro);
    const qint64& getId()const;
    const QString& getName()const;
    const QString & getMro()const;

    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий полей базы

    static array<QString, INSPECTIONVIEW_COLUMN> getFields() {
        return array<QString, INSPECTIONVIEW_COLUMN>{
            "id",
            "name",
            "mro"};
    }


    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {"Идентификатор", "Название", "МРО"};
        return jsonArray;
    }

    ///название модели

    static const QString getModelName() {
        return ModelWrapper::map()[model_];
    }




    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);


private:

    MQuery<InspectionView> query_;
    qint64 id_;
    QString name_;
    QString mro_;
};

#endif /* INSPECTIONVIEW_H */

