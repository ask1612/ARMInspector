/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   nsiEditForm.cpp
 * Author: kazun_as
 *
 * Created on 26 апреля 2021 г., 09:03
 */

#include "nsiEditForm.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

nsiEditForm::nsiEditForm(QWidget *parent) :
QDialog(parent), widget_(new Ui::nsiEditForm) {
    widget_->setupUi(this);
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

nsiEditForm::~nsiEditForm() {
    delete widget_;
}
///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::nsiEditForm* nsiEditForm::getUI() {
    return widget_;
}
