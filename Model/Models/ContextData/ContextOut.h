/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContextOut.h
 * Author: kazun_as
 *
 * Created on 29 июля 2021 г., 12:08
 */

#ifndef CONTEXTOUT_H
#define CONTEXTOUT_H
#define REPORTOUT_H
#include <QtCore/QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include "JsonSerializable.h"
#include "Model.h"
#include <array>
#include <QSqlQuery>
#include <MQuery.h>
#include "ModelWrapper.h"
#define CONTEXTOUT_COLUMN 2
using namespace std;

class ContextOut : public JsonSerializable {
public:
    static ModelWrapper::Model model_;

    enum Column {
        REGNUM = 0,
        FIO
    };
    ContextOut();
    virtual ~ContextOut();
    ///Функции чтения - записи полей класса
    void setRegnum(const QString&);
    void setFio(const QString&);
    const QString& getRegnum()const;
    const QString& getFio()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий полей базы

    static array<QString, CONTEXTOUT_COLUMN> getFields() {
        return array<QString, CONTEXTOUT_COLUMN>{
            "reg_num",
            "fio_penalized"};
    }
private:
    QString regnum_;
    QString fio_;

};

#endif /* CONTEXTOUT_H */

