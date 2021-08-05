/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptRowEditForm.h
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 15:25
 */

#ifndef _RPTCOLUMNEDITFORM_H
#define _RPTCOLUMNEDITFORM_H

#include "ui_RptRowEditForm.h"
//using namespace std;

class RptRowEditForm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit RptRowEditForm(QWidget *parent = 0);
    virtual ~RptRowEditForm();
    ///Получить ссылку на виджет
    Ui::RptRowEditForm* getUI();


private:
    Ui::RptRowEditForm* widget_;
};

#endif /* _RPTCOLUMNEDITFORM_H */
