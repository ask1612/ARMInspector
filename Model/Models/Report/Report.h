/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Report.h
 * Author: kazun_as
 *
 * Created on 19 мая 2021 г., 15:58
 */

#ifndef REPORT_H
#define REPORT_H
#include <QtCore/QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include "JsonSerializable.h"
#include "Model.h"
#include <array>
#include <QSqlQuery>
#include <MQuery.h>
#include "ModelWrapper.h"
#include "Report/ReportOut.h"
#define REPORT_COLUMN 5
using namespace std;

class Report : public JsonSerializable {
public:
    static ModelWrapper::Model model_;

    enum Column {
        MRO = 0,
        MON,
        YEAR,
        NUMROW,
        CUMMULATIVE
    };

    Report();
    virtual ~Report();
    ///Функции чтения - записи полей класса
    void setMro(const qint64&);
    void setMon(const qint64&);
    void setYear(const qint64&);
    void setNumrow(const qint64&);
    void setCummulative(const qint64&);
    const qint64& getMro()const;
    const qint64& getMon()const;
    const qint64& getYear()const;
    const qint64& getNumrow()const;
    const qint64& getCummulative()const;

    void setOutModel(const ReportOut&);
    const ReportOut& getOutModel()const;


    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;
    ///Список названий полей базы

    static array<QString, REPORT_COLUMN> getFields() {
        return array<QString, REPORT_COLUMN>{
            "mro",
            "mon",
            "year",
            "numrow",
            "cummulative"};
    }

    ///название модели

    static const QString getModelName() {
        return ModelWrapper::map()[model_];
    }

    void bindData(QSqlQuery* asSqlQuery);
    const QString& call();


private:
    MQuery<Report> query_;
    qint64 mro_; //МРО
    qint64 mon_; //отчётный месяц
    qint64 year_; //отчётный год 
    qint64 numrow_; //номер строки отчёта 
    qint64 cummulative_; //накопление для итоговых колонок
};

#endif /* REPORT_H */

