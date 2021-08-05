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
 * File:   userEditFrm.cpp
 * Author: kazun
 *
 * Created on 8 апреля 2021 г., 21:18
 */

#include "userEditFrm.h"
//-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

userEditFrm::userEditFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::userEditFrm) {
    widget_->setupUi(this);
}
//-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

userEditFrm::~userEditFrm() {
    delete widget_;
}
//-----------------------------------------------------------------------------
///
///         получить указатель на виджет окна
///          
///-----------------------------------------------------------------------------

Ui::userEditFrm* userEditFrm::getWidget() {
    return widget_;
}
//-----------------------------------------------------------------------------
///
///         получить список инспекций
///          
///-----------------------------------------------------------------------------

const QList<Inspection>& userEditFrm::getInspections()const {
    return inspections_;
};

///-----------------------------------------------------------------------------
///
///         Инициализировать список инспекций и
///         добавить элементы выпадающего списка QCcomboBox      
///          
///-----------------------------------------------------------------------------

void userEditFrm::setInspections(const QList<Inspection>& inspections) {
    inspections_ = inspections;
    this->getWidget()->comboBoxInspection->clear();
    for (auto& t : inspections_) {
        this->getWidget()->comboBoxInspection->addItem(t.getName());
    }

}

