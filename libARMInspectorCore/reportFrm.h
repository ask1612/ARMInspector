/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reportFrm.h
 * Author: kazun_as
 *
 * Created on 28 июня 2021 г., 11:56
 */

#ifndef _REPORTFRM_H
#define _REPORTFRM_H

#include "ui_reportFrm.h"

class reportFrm : public QMainWindow {
    Q_OBJECT
public:
    reportFrm();
    virtual ~reportFrm();
private:
    Ui::reportFrm widget;
};

#endif /* _REPORTFRM_H */
