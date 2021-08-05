/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 **
 **             Класс модели пользователя UserView.
 **             Используются для вывода данных о пользователе списком
 **
 ****************************************************************************/

/* 
 * File:   UserView.h
 * Author: kazun_as
 *
 * Created on 5 апреля 2021 г., 10:41
 */

#ifndef UserView_H
#define UserView_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <array>
#include <MQuery.h>
#include "ModelWrapper.h"
#define USERV_COLUMN 4

using namespace std;


class UserView : public JsonSerializable, Model {
public:
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        FIO,
        INSPECTION,
        NAME
    };
    ///конструктор
    UserView();
    ///деструктор
    virtual ~UserView();
    ///Функции чтения - записи полей класса
    void setId(const qint64& id);
    void setFio(const QString& fio);
    void setInspection(const QString& inspection);
    void setName(const QString& name);
    const qint64& getId()const;
    const QString& getFio()const;
    const QString& getInspection()const;
    const QString& getName()const;
    ///Функции сериализации объекта класса
    ///Считывание JSON объкта в поля класса
    void read(const QJsonObject &jsonObj);
    ///Запись полей класса в JSON объкт. 
    void write(QJsonObject &jsonObj) const;

    ///Список названий полей базы

    static array<QString, USERV_COLUMN> getFields() {
        return array<QString, USERV_COLUMN>{
            "id",
            "fio",
            "inspection",
            "name"};
    }

    ///Список названий колонок модели

    static const QJsonArray getColumnArray() {
        const QJsonArray jsonArray = {"Идентификатор", "ФИО", "Инспекция", "Имя пользователя"};
        return jsonArray;
    }

    ///название модели

    static const QString getModelName() {
        return ModelWrapper::map()[model_];
    }

    ///SQL запрос вывода данных


    ///SQL запрос удаления экземпляра модели в  базе данных

    static const QString delQuery() {
        return QString("Delete   from user ");
    }
    ///Интерфейс модели.
    ///Получить  данные  о мрдели.
    virtual const QVariant getData(const int&) const;
    ///Установить  данные  модели.
    virtual void setData(const int&, const QVariant&);

private:
    MQuery<UserView> query_;



    qint64 id_;
    QString fio_;
    QString inspection_;
    QString name_;

};

#endif /* UserView_H */

