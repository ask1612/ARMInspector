/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumnView.h
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 13:48
 */

#ifndef RPTCOLUMNVIEW_H
#define RPTCOLUMNVIEW_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include "ModelWrapper.h"
#include <MQuery.h>
#include <array>
#define RPTVIEW_COLUMN 4
using namespace std;
class RptColumnView: public JsonSerializable, Model {
public:
static ModelWrapper::Model model_;
   enum Column {
        ID = 0,
        ARTICLE,
        SUBJECT,
        COL
    };
    ///Кострктор
    RptColumnView();
    ///Деструктор
    virtual ~RptColumnView();
 void setId(const qint64& id);
    void setArticle(const QString& article);
    void setSubject(const QString& offense_subject);
    void setCol(const qint64& col);
    const qint64& getId()const;
    const QString& getArticle()const;
    const QString& getSubject()const;
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

    static array<QString, RPTVIEW_COLUMN> getFields() {
        return array<QString, RPTVIEW_COLUMN>{
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



private:
    MQuery<RptColumnView> query_;
    //Поля класса
    ///Идентификатор пользователя
    qint64 id_;
    ///Статья КоАП
    QString article_;
    ///Тип нарушителя
    QString subject_;
    ///Колонка отчёта
    qint64 col_;

};

#endif /* RPTCOLUMNVIEW_H */

