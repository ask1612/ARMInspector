/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nsi.h
 * Author: kazun_as
 *
 * Created on 23 апреля 2021 г., 16:15
 */

#ifndef NSI_H
#define NSI_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <array>
#include <MQuery.h>
#include <QSqlQuery>
#include "ModelWrapper.h"

#define NSI_COLUMN 2
#define NSI_ARTICLE "71"
#define NSI_SUBJECT "5"
#define NSI_NUM    "numNSI"
#define DATA    "data"
#define ID_    "ID"

using namespace std;

class Nsi : public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NAME
    };
    Nsi();
    Nsi(const QString& num);
    virtual ~Nsi();
    void setId(const qint64& id);
    void setName(const QString& name);
    const qint64& getId()const;
    const QString& getName()const;
    static QString num_;


    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;



    ///Список названий полей базы

    static array<QString, NSI_COLUMN> getFields() {
        return array<QString, NSI_COLUMN>{
            "id",
            "name_" + Nsi::num_};
    }


    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "№",
            "Название "
        };
        return jsonArray;
    }


    ///название модели

    //static const QString getModelName() {
    //    return QString("nsi_" + Nsi::num_);
    // }

    static const QString getModelName() {
        return ModelWrapper::map()[model_] + Nsi::num_;
    }


    ///Интерфейс модели.
    ///Получить  данные  о модели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);
    void bindData(QSqlQuery* asSqlQuery);
    const QString& update();
    const QString& insert();


private:

    MQuery<Nsi> query_;


    qint64 id_;
    QString name_;
};

#endif /* NSI_H */

