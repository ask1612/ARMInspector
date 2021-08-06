/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:  Review.h
 * Author: kazun_as
 *
 * Created on 4 августа 2021 г., 12:29
 */

#ifndef REVIEW_H
#define REVIEW_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <MQuery.h>
#include "ModelWrapper.h"
#include <array>
#include <QSqlQuery>
#define REVIEW_COLUMN 7
#define ID_    "ID"
using namespace std;

class Review : public JsonSerializable, Model {
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NUM,
        VIEW_DATE,
        NSI_11,
        IN_NUM,
        IN_DATE,
        DOC_ID
    };

public:
    Review();
    virtual ~Review();
    const qint64& getId() const;
    const qint64& getNum() const;
    const QString& getViewDate() const;
    const qint64& getNsi11() const;
    const qint64& getInNum() const;
    const QString& getInDate() const;
    const qint64& getDocId() const;

    void setId(const qint64&);
    void setNum(const qint64&);
    void setViewDate(const QString&);
    void setNsi11(const qint64&);
    void setInNum(const qint64&);
    void setInDate(const QString&);
    void setDocId(const qint64&);

    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт.
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "",
            "Исходящий №",
            "Дата",
            "Кому направлено",
            "Входящий №",
            "Дата",
            ""
        };
        return jsonArray;
    }

    ///Список названий полей базы

    static array<QString, REVIEW_COLUMN> getFields() {
        return array<QString, REVIEW_COLUMN>{
            "id",
            "num",
            "view_date",
            "nsi_11",
            "in_num",
            "in_date",
            "doc_id"};
    }


    ///название модели

    static const QString getModelName() {
        return ModelWrapper::map()[model_];
    }

    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    //virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    ////virtual void setData(const int&, const QVariant&);
    ///привязать парвметры sql запроса к данным
    void bindData(QSqlQuery* asSqlQuery);
    ///сформировать sql запрос вставки новой записи
    ///SQL запросы


private:
    MQuery<Review> query_;
    //Поля класса
    qint64 id_;
    qint64 num_;
    QString view_date_;
    qint64 nsi_11_;
    qint64 in_num_;
    QString in_date_;
    qint64 doc_id_;
};
#endif /* REVIEW_H */

