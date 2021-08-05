/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RptRowEditForm.cpp
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 15:25
 */

#include "RptRowEditForm.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

RptRowEditForm::RptRowEditForm(QWidget *parent) :
QDialog(parent), widget_(new Ui::RptRowEditForm) {
    widget_->setupUi(this);
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

RptRowEditForm::~RptRowEditForm() {
    delete widget_;
}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::RptRowEditForm* RptRowEditForm::getUI() {
    return widget_;
}

