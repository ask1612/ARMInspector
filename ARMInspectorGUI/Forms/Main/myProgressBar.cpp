/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   myProgressBar.cpp
 * Author: kazun_as
 *
 * Created on 21 мая 2021 г., 10:30
 */

#include "myProgressBar.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

myProgressBar::myProgressBar(QWidget *parent) :
QDialog(parent), widget_(new Ui::myProgressBar) {
    widget_->setupUi(this);
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

myProgressBar::~myProgressBar() {
    delete widget_;

}

///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::myProgressBar* myProgressBar::getUI() {
    return widget_;
}
