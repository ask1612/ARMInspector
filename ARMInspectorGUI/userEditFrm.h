/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 ** 
 **             РЕДАКТИРОВАНИЕ ПОЛЬЗОВАТЕЛЯ
 **             Класс окна редактирования  пользователя -userEditFrm.
 **
 ****************************************************************************/

/* 
 * File:   userEditFrm.h
 * Author: kazun
 *
 * Created on 8 апреля 2021 г., 21:18
 */

#ifndef _USEREDITFRM_H
#define _USEREDITFRM_H

#include "ui_userEditFrm.h"
//#include "User/User.h"
#include "Inspection/Inspection.h"

class userEditFrm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit userEditFrm(QWidget *parent = 0);
    ///деструктор
    virtual ~userEditFrm();
    ///получить указатель на виджет окна
    Ui::userEditFrm* getWidget();
    ///получить список инспекций 
    const QList<Inspection>& getInspections() const;
    ///инициализировать список инспекций
    void setInspections(const QList<Inspection>&);

private:
    ///указатель на виджет окна
    Ui::userEditFrm* widget_;
    ///список инспекций
    QList<Inspection> inspections_;

};

#endif /* _USEREDITFRM_H */
