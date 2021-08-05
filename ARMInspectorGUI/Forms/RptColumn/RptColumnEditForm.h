/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumnEditForm.h
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 15:25
 */

#ifndef _RPTCOLUMNEDITFORM_H
#define _RPTCOLUMNEDITFORM_H

#include "ui_RptColumnEditForm.h"
#include "Nsi/Nsi.h"
#include <QHash>
//using namespace std;

class RptColumnEditForm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit RptColumnEditForm(QWidget *parent = 0);
    virtual ~RptColumnEditForm();
    ///Получить ссылку на виджет
    Ui::RptColumnEditForm* getUI();
    ///получить список статей
    //const QList<Nsi>& getListArticle() const;
    const QHash <qint64, QString>& getMapArticle() const;
    /// инициализировать список статей
    void setMapArticle(const QList<Nsi>&);
    ///получить список субъектов АП
    //const QList<Nsi>& getListSubject() const;
    const QHash <qint64, QString>& getMapSubject() const;
    /// инициализировать список субъектов АП
    void setMapSubject(const QList<Nsi>&);


private:
    Ui::RptColumnEditForm* widget_;
    ///список статей
    //QList<Nsi> listarticle_;
    QHash <qint64, QString> maparticle_;
    ///список  субъектов АП
    //QList<Nsi> listsubject_;
    QHash <qint64, QString> mapsubject_;
};

#endif /* _RPTCOLUMNEDITFORM_H */
