/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:  Prepare.h
 * Author: kazun_as
 *
 * Created on 4 августа 2021 г., 12:29
 */

#ifndef PREPARE_H
#define PREPARE_H
#include <QtCore/QJsonObject>
#include "JsonSerializable.h"
#include <QVariant>
#include <QJsonArray>
#include "Model.h"
#include <MQuery.h>
#include "ModelWrapper.h"
#include <array>
#include <QSqlQuery>
#define PREPARE_COLUMN 19
#define ID_    "ID"
using namespace std;

class Prepare : public JsonSerializable, Model {
    static ModelWrapper::Model model_;

    enum Column {
        ID = 0,
        INSPECTOR_ID,
        STATUTE_NUM,
        STATUTE_DATE,
        FIO_PENALIZED,
        SUMMA,
        PROTOCOL_NUM,
        PROTOCOL_DATE,
        PROTOCOL_FIO,
        NSI_10,
        DOC_NUM,
        DOC_DATE,
        ADDRESSAT,
        ARTICL_7,
        ARTICL_5,
        ARTICL_51,
        ARTICLE,
        PUNKT,
        DOC_ID
    };

public:
    Prepare();
    virtual ~Prepare();
    const qint64& getId() const;
    const qint64& getInspectorId() const;
    const qint64& getStatuteNum() const;
    const QString& getStatuteDate() const;
    const QString& getFioPenalized() const;
    const double& getSumma() const;
    const qint64& getProtocolNum() const;
    const QString& getProtocolDate() const;
    const QString& getProtocolFio() const;
    const qint64& getNnsi10() const;
    const qint64& getDocNum() const;
    const QString& getDocDate() const;
    const QString& getAddressat() const;
    const qint64& getArticl7() const;
    const qint64& getArticl5() const;
    const qint64& getArticl51() const;
    const qint64& getArticle() const;
    const qint64& getPunkt() const;
    const qint64& getDocId() const;

    void setId(const qint64&);
    void setInspectorId(const qint64&);
    void setStatuteNum(const qint64&);
    void setStatuteDate(const QString&);
    void setFioPenalized(const QString&);
    void setSumma(const double&);
    void setProtocolNum(const qint64&);
    void setProtocolDate(const QString&);
    void setProtocolFio(const QString&);
    void setNnsi10(const qint64&);
    void setDocNum(const qint64&);
    void setDocDate(const QString&);
    void setAddressat(const QString&);
    void setArticl7(const qint64&);
    void setArticl5(const qint64&);
    void setArticl51(const qint64&);
    void setArticle(const qint64&);
    void setPunkt(const qint64&);
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
            "Инспектор, осуществляющий подготовку дела к рассмотрению",
            "№ постановления",
            "Дата постановления",
            "На кого вынесно (ФИО)",
            "Сумма штрафа",
            "№ протокола",
            "Дата протокола",
            "На кого составлен (ФИО)",
            "Вид документа",
            "№ документа",
            "Дата",
            "Адресат",
            "Статья КоАП",
            "Тип нарушителя",
            "Тип документа",
            "Основание(статья ПИКоАП)",
            "Пункт",
            ""
        };
        return jsonArray;
    }

    ///Список названий полей базы

    static array<QString, PREPARE_COLUMN> getFields() {
        return array<QString, PREPARE_COLUMN>{
            "id",
            "inspector_id",
            "statute_num",
            "statute_date",
            "fio_penalized",
            "summa",
            "protocol_num",
            "protocol_date",
            "protocol_fio",
            "nsi_10",
            "doc_num",
            "doc_date",
            "addressat",
            "articl_7",
            "articl_5",
            "articl_51",
            "article",
            "punkt",
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
    MQuery<Prepare> query_;
    //Поля класса
    qint64 id_;
    qint64 inspector_id_;
    qint64 statute_num_;
    QString statute_date_;
    QString fio_penalized_;
    double summa_;
    qint64 protocol_num_;
    QString protocol_date_;
    QString protocol_fio_;
    qint64 nsi_10_;
    qint64 doc_num_;
    QString doc_date_;
    QString addressat_;
    qint64 articl_7_;
    qint64 articl_5_;
    qint64 articl_51_;
    qint64 article_;
    qint64 punkt_;
    qint64 doc_id_;
};
#endif /* PREPARE_H */

