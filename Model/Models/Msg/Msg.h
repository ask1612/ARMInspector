/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Msg.h
 * Author: kazun_as
 *
 * Created on 4 августа 2021 г., 12:29
 */

#ifndef MSG_H
#define MSG_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <MQuery.h>
#include "ModelWrapper.h"
#include <array>
#include <QSqlQuery>
#define MSG_COLUMN 6
#define ID_    "ID"
using namespace std;

class Msg : public JsonSerializable, Model {
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NUM,
        MSG_DATE,
        NSI_1,
        TO_WHO,
        DOC_ID
    };

public:
    Msg();
    virtual ~Msg();
    const qint64& getId() const;
    const QString& getNum() const;
    const QString& getMsgDate() const;
    const qint64& getNsi1() const;
    const QString& getToWho() const;
    const qint64& getDocId() const;
    void setId(const qint64&);
    void setNum(const QString&);
    void setMsgDate(const QString&);
    void setNsi1(const qint64&);
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
            "Входящий №",
            "Дата",
            "От кого поступило",
            "На кого поступило (ФИО)",
            ""
        };
        return jsonArray;
    }

    ///Список названий полей базы

    static array<QString, MSG_COLUMN> getFields() {
        return array<QString, MSG_COLUMN>{
            "id",
            "num",
            "msg_date",
            "nsi_1",
            "to_who",
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
    //virtual void setData(const int&, const QVariant&);
    ///привязать парвметры sql запроса к данным
    void bindData(QSqlQuery* asSqlQuery);
    ///сформировать sql запрос вставки новой записи
    ///SQL запросы


private:
    MQuery<Msg> query_;
    //Поля класса
    qint64 id_;
    QString num_;
    QString msg_date_;
    qint64 nsi_1_;
    QString to_who_;
    qint64 doc_id_;
};

#endif /* MSG_H */

