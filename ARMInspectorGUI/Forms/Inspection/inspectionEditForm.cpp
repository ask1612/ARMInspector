/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   inspectionEditForm.cpp
 * Author: kazun_as
 *
 * Created on 14 мая 2021 г., 16:11
 */

#include "inspectionEditForm.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

inspectionEditForm::inspectionEditForm(QWidget *parent) :
QDialog(parent), widget_(new Ui::inspectionEditForm) {
    widget_->setupUi(this);
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

inspectionEditForm::~inspectionEditForm() {
    delete widget_;
}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::inspectionEditForm* inspectionEditForm::getUI() {
    return widget_;
}
///-----------------------------------------------------------------------------
///
///         Получить список инспекций.
///          
///-----------------------------------------------------------------------------

const QList<Mro>& inspectionEditForm::getListMro()const {
    return listmro_;
};

///-----------------------------------------------------------------------------
///
///         Инициализировать список инспекций и
///         добавить элементы выпадающего списка QCcomboBox      
///          
///-----------------------------------------------------------------------------

void inspectionEditForm::setListMro(const QList<Mro>& listmro) {
    listmro_ = listmro;
    this->getUI()->comboBox->clear();
    for (auto& t : listmro_) {
        this->getUI()->comboBox->addItem(t.getName());
    }
}

///-----------------------------------------------------------------------------
/// 
///         преобразовать список инспекция        
///
///-----------------------------------------------------------------------------

QHash <qint64, QString> inspectionEditForm::mapMro() {
    QHash <qint64, QString> mapmro;
    for (auto& t : listmro_) {
        mapmro.insert(t.getId(), t.getName());
    }
    return mapmro;
}
