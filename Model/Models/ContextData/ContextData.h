/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContextData.h
 * Author: kazun_as
 *
 * Created on 29 июля 2021 г., 11:39
 */

#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
#include <QtCore/QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include "JsonSerializable.h"
#include "Model.h"
#include <array>
#include <QSqlQuery>
#include <MQuery.h>
#include "ModelWrapper.h"
#include "ContextData/ContextOut.h"
#define CONTEXTDATA_COLUMN 6
using namespace std;

class ContextData : public JsonSerializable {
public:
    static ModelWrapper::Model model_;

    enum Column {
        MRO = 0,
        MON,
        YEAR,
        NUMROW,
        NUMCOL,
        CUMMULATIVE
    };
    ContextData();
    virtual ~ContextData();
    ///Функции чтения - записи полей класса
    void setMro(const qint64&);
    void setMon(const qint64&);
    void setYear(const qint64&);
    void setNumrow(const qint64&);
    void setNumcol(const qint64&);
    void setCummulative(const qint64&);
    const qint64& getMro()const;
    const qint64& getMon()const;
    const qint64& getYear()const;
    const qint64& getNumrow()const;
    const qint64& getNumcol()const;
    const qint64& getCummulative()const;

    //void setOutModel(const ContextOut&);
    //const ContextOut& getOutModel()const;


    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;
    ///Список названий полей базы

    static array<QString, CONTEXTDATA_COLUMN> getFields() {
        return array<QString, CONTEXTDATA_COLUMN>{
            "mro",
            "mon",
            "year",
            "numrow",
            "numcol",
            "cummulative"};
    }

    ///название модели

    static const QString getModelName() {
        return ModelWrapper::map()[model_];
    }

    void bindData(QSqlQuery* asSqlQuery);
    const QString& call();


private:
    MQuery<ContextData> query_;
    qint64 mro_; //МРО
    qint64 mon_; //отчётный месяц
    qint64 year_; //отчётный год 
    qint64 numrow_; //номер строки отчёта 
    qint64 numcol_; //номер колонки отчёта 
    qint64 cummulative_; //накопление для итоговых колонок

};

#endif /* CONTEXTDATA_H */

