/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nsiEditForm.h
 * Author: kazun_as
 *
 * Created on 26 апреля 2021 г., 09:03
 */

#ifndef _NSIEDITFORM_H
#define _NSIEDITFORM_H

#include "ui_nsiEditForm.h"

class nsiEditForm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit nsiEditForm(QWidget *parent = 0);
    ~nsiEditForm();
    ///Получить ссылку на виджет
    Ui::nsiEditForm* getUI();

private:
    Ui::nsiEditForm* widget_;
};

#endif /* _NSIEDITFORM_H */
