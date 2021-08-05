/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mroEditForm.h
 * Author: kazun_as
 *
 * Created on 13 мая 2021 г., 14:47
 */

#ifndef _MROEDITFORM_H
#define _MROEDITFORM_H

#include "ui_mroEditForm.h"
#include "Inspection/Inspection.h"

class mroEditForm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit mroEditForm(QWidget *parent = 0);
    virtual ~mroEditForm();
    ///Получить ссылку на виджет
    Ui::mroEditForm* getUI();
    ///получить список инспекций
    const QList<Inspection>& getInspections() const;
    /// инициализировать список инспекций
    void setInspections(const QList<Inspection>&);
    /// преобразовать список  в Hash
    QHash <qint64, QString>  mapInspections();


private:
    Ui::mroEditForm* widget_;
    ///список инспекций
    QList<Inspection> inspections_;
};

#endif /* _MROEDITFORM_H */
