/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumn.h
 * Author: kazun_as
 *
 * Created on 23 апреля 2021 г., 15:14
 */

#ifndef RPTCOLUMN_H
#define RPTCOLUMN_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include "ModelWrapper.h"
#include <MQuery.h>
#include <array>
#include <QSqlQuery>
#define RPT_COLUMN 4

using namespace std;

class RptColumn : public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        ARTICLE,
        SUBJECT,
        COL
    };
    RptColumn();
    virtual ~RptColumn();
    void setId(const qint64& id);
    void setArticle(const qint64& article);
    void setSubject(const qint64& offense_subject);
    void setCol(const qint64& col);
    const qint64& getId()const;
    const qint64& getArticle()const;
    const qint64& getSubject()const;
    const qint64& getCol()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "Идентификатор",
            "Статья",
            "Тип нарушителя",
            "№ колонки отчёта",
        };
        return jsonArray;
    }
    ///Список названий полей базы

    static array<QString, RPT_COLUMN> getFields() {
        return array<QString, RPT_COLUMN>{
            "id",
            "article",
            "subject",
            "col"};
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
    MQuery<RptColumn> query_;
    //Поля класса
    ///Идентификатор пользователя
    qint64 id_;
    ///Статья КоАП
    qint64 article_;
    ///Тип нарушителя
    qint64 subject_;
    ///Колонка отчёта
    qint64 col_;


};

#endif /* RPTCOLUMN_H */

