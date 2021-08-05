/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   inspectionEditForm.h
 * Author: kazun_as
 *
 * Created on 14 мая 2021 г., 16:11
 */

#ifndef _INSPECTIONEDITFORM_H
#define _INSPECTIONEDITFORM_H

#include "ui_inspectionEditForm.h"
#include "Mro/Mro.h"

class inspectionEditForm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit inspectionEditForm(QWidget *parent = 0);
    virtual ~inspectionEditForm();
    ///Получить ссылку на виджет
    Ui::inspectionEditForm* getUI();
    ///получить список инспекций
    const QList<Mro>& getListMro() const;
    /// инициализировать список инспекций
    void setListMro(const QList<Mro>&);
    /// преобразовать список  в Hash
    QHash <qint64, QString> mapMro();


private:
    Ui::inspectionEditForm* widget_;
    ///список инспекций
    QList<Mro> listmro_;
};

#endif /* _INSPECTIONEDITFORM_H */
