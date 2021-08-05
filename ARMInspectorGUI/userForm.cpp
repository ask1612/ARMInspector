/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 ** 
 **             ДОБАВЛЕНИЕ НОВОГО ПОЛЬЗОВАТЕЛЯ
 **             Класс окна добавления нового  пользователя -myForm.
 **
 ****************************************************************************/

/*
 * File:   userForm.cpp
 * Author: kazun
 *
 * Created on 3 апреля 2021 г., 16:35
 */

#include "userForm.h"
///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

userForm::userForm(QWidget *parent) :
QDialog(parent), widget_(new Ui::userForm) {
    widget_->setupUi(this);


}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

userForm::~userForm() {
    delete widget_;
}

///-----------------------------------------------------------------------------
///
///         Получить указатель на виджет окна.
///          
///-----------------------------------------------------------------------------

Ui::userForm* userForm::getWidget() {
    return widget_;
}

///-----------------------------------------------------------------------------
///
///         Получить список инспекций.
///          
///-----------------------------------------------------------------------------

const QList<Inspection>& userForm::getInspections()const {
    return inspections_;
};

///-----------------------------------------------------------------------------
///
///         Инициализировать список инспекций и
///         добавить элементы выпадающего списка QCcomboBox      
///          
///-----------------------------------------------------------------------------

void userForm::setInspections(const QList<Inspection>& inspections) {
    inspections_ = inspections;
    this->getWidget()->comboBoxInspection->clear();
    for (auto& t : inspections_) {
        this->getWidget()->comboBoxInspection->addItem(t.getName());
    }

}

///-----------------------------------------------------------------------------
/// 
///         преобразовать список инспекция        
///
///-----------------------------------------------------------------------------

QHash <qint64, QString> userForm::mapInspections() {
    QHash <qint64, QString> mapinspections;
    for (auto& t : inspections_) {
        mapinspections.insert(t.getId(), t.getName());
    }
    return mapinspections;
}


