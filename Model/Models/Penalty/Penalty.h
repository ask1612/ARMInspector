/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:  Penalty.h
 * Author: kazun_as
 *
 * Created on 4 августа 2021 г., 12:29
 */

#ifndef PENALTY_H
#define PENALTY_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <MQuery.h>
#include "ModelWrapper.h"
#include <array>
#include <QSqlQuery>
#define PENALTY_COLUMN 19
#define ID_    "ID"
using namespace std;

class Penalty : public JsonSerializable, Model {
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        NSI_4,
        NSI_11,
        STATUTE_NUM,
        STATUTE_DATE,
        FORCE_DATE,
        FIO_PENALIZED,
        NSI_5,
        NSI_6,
        NSI_7,
        NSI_8,
        SUMMA,
        DOC_ID
    };

public:
    Penalty();
    virtual ~Penalty();
    const qint64& getIid() const;
    const qint64& getNsi4() const;
    const qint64& getNsi11() const;
    const qint64& getStatuteNum() const;
    const QString& getStatuteDate() const;
    const QString& getForceDate() const;
    const QString& getFioPenalized() const;
    const qint64& getNsi5() const;
    const qint64& getNsi6() const;
    const qint64& getNsi7() const;
    const qint64& getNsi8() const;
    const double& getSsumma() const;
    const qint64& getDocId() const;

    void setIid(const qint64&);
    void setNsi4(const qint64&);
    void setNsi11(const qint64&);
    void setStatuteNum(const qint64&);
    void setStatuteDate(const QString&);
    void setForceDate(const QString&);
    void setFioPenalized(const QString&);
    void setNsi5(const qint64&);
    void setNsi6(const qint64&);
    void setNsi7(const qint64&);
    void setNsi8(const qint64&);
    void setSsumma(const double&);
    void setDocId(const qint64&);

    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj);

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {
            "",
            "Должностное лицо/Орган",
            "ФИО/Название органа",
            "№ постановления",
            "Дата постановления",
            "Дата вступления в зак. силу",
            "ФИО",
            "Должностное/Физ./Юр. лицо",
            "Должность",
            "Статья КоАП",
            "Вид взыскания",
            "Сумма штрафа",
            ""
        };
        return jsonArray;
    }

    ///Список названий полей базы

    static array<QString, PENALTY_COLUMN> getFields() {
        return array<QString, PENALTY_COLUMN>{
            "id",
            "nsi_4",
            "nsi_11",
            "statute_num",
            "statute_date",
            "force_date",
            "fio_penalized",
            "nsi_5",
            "nsi_6",
            "nsi_7",
            "nsi_8",
            "summa",
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
    MQuery<Penalty> query_;
    //Поля класса

    qint64 id_;
    qint64 nsi_4_;
    qint64 nsi_11_;
    qint64 statute_num_;
    QString statute_date_;
    QString force_date_;
    QString fio_penalized_;
    qint64 nsi_5_;
    qint64 nsi_6_;
    qint64 nsi_7_;
    qint64 nsi_8_;
    double summa_;
    qint64 doc_id_;
};
#endif /* PENALTY_H */

