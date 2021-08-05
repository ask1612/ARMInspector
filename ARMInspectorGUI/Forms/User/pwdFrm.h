/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pwdFrm.h
 * Author: kazun
 *
 * Created on 13 апреля 2021 г., 21:05
 */

#ifndef _PWDFRM_H
#define _PWDFRM_H

#include "ui_pwdFrm.h"

class pwdFrm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit pwdFrm(QWidget *parent = 0);
    ///деструктор
    virtual ~pwdFrm();
    ///получить указатель на виджет окна
    Ui::pwdFrm* getWidget();

private:
    Ui::pwdFrm* widget_;
};

#endif /* _PWDFRM_H */
