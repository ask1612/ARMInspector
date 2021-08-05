/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   pwdFrm.cpp
 * Author: kazun
 *
 * Created on 13 апреля 2021 г., 21:05
 */

#include "pwdFrm.h"

pwdFrm::pwdFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::pwdFrm) {
    widget_->setupUi(this);
}

pwdFrm::~pwdFrm() {
}


///-----------------------------------------------------------------------------
///
///         Получить указатель на виджет окна.
///          
///-----------------------------------------------------------------------------

Ui::pwdFrm* pwdFrm::getWidget() {
    return widget_;
}
