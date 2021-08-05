/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 **
 **             Класс модели инспекции Inspection.
 **
 ****************************************************************************/

/* 
 * File:   Inspection.h
 * Author: kazun
 *
 * Created on 3 апреля 2021 г., 21:58
 */

#ifndef INSPECTION_H
#define INSPECTION_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include "Model.h"
#include <QVariant>
#include <QJsonArray>
#include <array>
#include <MQuery.h>
#include "ModelWrapper.h"
#include <QSqlQuery>
#define INSPECTION_COLUMN 3
#define ID_    "ID"

using namespace std;

class Inspection : public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NAME,
        MRO
    };
    ///Конструктор
    Inspection();
    ///деструктор
    virtual ~Inspection();
    ///Функции чтения - записи полей класса
    void setId(const qint64& id);
    void setName(const QString& name);
    void setMro(const qint64& mro);
    const qint64& getId()const;
    const QString& getName()const;
    const qint64& getMro()const;

    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий полей базы

    static array<QString, INSPECTION_COLUMN> getFields() {
        return array<QString, INSPECTION_COLUMN>{
            "id",
            "name_i",
            "id_mro"};
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

    ///привязать парвметры sql запроса к данным
    void bindData(QSqlQuery* asSqlQuery);
    ///сформировать sql запрос вставки новой записи

    ///SQL запросы
    const QString& insert();
    const QString& update();



private:

    MQuery<Inspection> query_;
    qint64 id_;
    QString name_;
    qint64 mro_;

};

#endif /* INSPECTION_H */

