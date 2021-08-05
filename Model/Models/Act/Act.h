/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Act.h
 * Author: kazun_as
 *
 * Created on 4 августа 2021 г., 12:29
 */

#ifndef ACT_H
#define ACT_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <MQuery.h>
#include "ModelWrapper.h"
#include <array>
#include <QSqlQuery>
#define ACT_COLUMN 9
#define ID_    "ID"
using namespace std;

class Act : public JsonSerializable, Model {
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NUM,
        ACT_DATE,
        NSI_2,
        SUMMA,
        TICKET_DATE,
        TICKET_NUM,
        TO_WHO,
        DOC_ID
    };

public:
    Act();
    virtual ~Act();
    const qint64& getId() const;
    const QString& getNum() const;
    const QString& getActDate() const;
    const qint64& getNsi2() const;
    const double& getSumma() const;
    const QString& getToWho() const;
    const QString& getTicketDate() const;
    const qint64& getTicketNum() const;
    const qint64& getDocId() const;
    
    void setId(const qint64&);
    void setNum(const QString&);
    void setActDate(const QString&);
    void setNsi2(const qint64&);
    void setSumma(const double&);
    void setTicketDate(const QString&);
    void setTicketNum(const qint64&);
    void setToWho(const QString&);
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
            "№ акта",
            "Дата акта",
            "Кем составлен",
            "Сумма ущерба",
            "Дата квитанции об оплате",
            "№ квитанции об оплате",
            "На кого составлен (ФИО)",
            ""
        };
        return jsonArray;
    }

    ///Список названий полей базы

    static array<QString, ACT_COLUMN> getFields() {
        return array<QString, ACT_COLUMN>{
		"id",
		"num",
		"act_date",
		"nsi_2",
		"summa",
		"ticket_date",
		"ticket_num",
		"to_who",
		"doc_id"
        };
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
    MQuery<Act> query_;
    //Поля класса
    qint64 id_;
    QString num_;
    QString act_date_;
    qint64 nsi_2_;
    double  summa_;
    QString ticket_date_;
    qint64 ticket_num_;
    QString to_who_;
    qint64 doc_id_;
};

#endif /* ACT_H */

