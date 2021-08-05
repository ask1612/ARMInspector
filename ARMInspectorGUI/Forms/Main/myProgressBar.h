/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myProgressBar.h
 * Author: kazun_as
 *
 * Created on 21 мая 2021 г., 10:30
 */



#ifndef _MYPROGRESSBAR_H
#define _MYPROGRESSBAR_H

#include "ui_myProgressBar.h"

class myProgressBar : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit myProgressBar(QWidget *parent = 0);
    ///деструктор
    ~myProgressBar();
    ///Получить ссылку на виджет
    Ui::myProgressBar* getUI();
private:
    Ui::myProgressBar* widget_;
};

#endif /* _MYPROGRESSBAR_H */
