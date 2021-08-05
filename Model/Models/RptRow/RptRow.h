/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptRow.h
 * Author: kazun_as
 *
 * Created on 17 мая 2021 г., 13:00
 */

#ifndef RPTROW_H
#define RPTROW_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include "ModelWrapper.h"
#include <MQuery.h>
#include <array>
#include <QSqlQuery>
#define RPTROW_COLUMN 5

using namespace std;

class RptRow : public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NPP,
        NAME,
        FORMULA,
        ROW
    };
    RptRow();
    virtual ~RptRow();
    void setId(const qint64&);
    void setNpp(const QString&);
    void setName(const QString&);
    void setFormula(const QString&);
    void setRow(const qint64&);
    const qint64& getId() const;
    const QString& getNpp() const;
    const QString& getName() const;
    const QString& getFormula() const;
    const qint64& getRow() const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "Идентификатор",
            "№ п/п",
            "Название",
            "Формула",
            "№ стр.",
        };
        return jsonArray;
    }
    ///Список названий полей базы

    static array<QString, RPTROW_COLUMN> getFields() {
        return array<QString, RPTROW_COLUMN>{
            "id",
            "npp",
            "name",
            "formula",
            "row"};
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
    MQuery<RptRow> query_;
    //Поля класса
    ///Идентификатор пользователя
    qint64 id_;
    ///номер по порядку
    QString npp_;
    ///название
    QString name_;
    ///формула
    QString formula_;
    ///строка отчёта
    qint64 row_;


};

#endif /* RPTROW_H */

