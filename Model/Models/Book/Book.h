/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Book.h
 * Author: kazun_as
 *
 * Created on 4 августа 2021 г., 12:29
 */

#ifndef BOOK_H
#define BOOK_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <MQuery.h>
#include "ModelWrapper.h"
#include <array>
#include <QSqlQuery>
#define BOOK_COLUMN 8
#define ID_    "ID"
using namespace std;

class Book : public JsonSerializable, Model {
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        DOC_DATE,
        INSPECTOR_ID,
        PREPAR_INSP,
        REG_NUM,
        REG_DATE,
        DOC_TYPE,
        STATE
    };

public:
    Book();
    virtual ~Book();
    void setId(const qint64& );
    void setDocDate(const QString& );
    void setInspectorId(const qint64& );
    void setPrepareIns(const qint64& );
    void setRegNum(const QString& );
    void setRegDate(const QString& );
    void setDocsType(const qint64& );
    void setState(const qint64& );
    const qint64& getId() const;
    const QString& getDocDate() const;
    const qint64& getInspectorId() const;
    const qint64& getPrepareIns()const;
    const QString& getRegNum()const;
    const QString& getRegDate() const;
    const qint64& getDocsType() const;
    const qint64& getState() const;

    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "Идентификатор",
            "Дата",
            "Инспектор",
            "Инспектор подготовки",
            "Регистрационный номер",
            "Дата регистрации",
            "Тип документа"
            "Состояние"
        };
        return jsonArray;
    }

    ///Список названий полей базы

    static array<QString, BOOK_COLUMN> getFields() {
        return array<QString, BOOK_COLUMN>{
            "id",
            "doc_date",
            "inspector_id",
            "prepar_insp",
            "reg_num",
            "reg_date",
            "doc_type",
            "state"};
    }


    ///название модели

    static const QString getModelName() {
        return ModelWrapper::map()[model_];
    }

    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    //virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    //virtual void setData(const int&, const QVariant&);
    ///привязать парвметры sql запроса к данным
    void bindData(QSqlQuery* asSqlQuery);
    ///сформировать sql запрос вставки новой записи

    ///SQL запросы


private:
    MQuery<Book> query_;
    //Поля класса
    qint64 id_;
    QString doc_date_;
    qint64 inspector_id_;
    qint64 prepar_insp_;
    QString reg_num_;
    QString reg_date_;
    qint64 doc_type_;
    qint64 state_;

};

#endif /* BOOK_H */

