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
 * File:   userForm.h
 * Author: kazun
 *
 * Created on 3 апреля 2021 г., 16:35
 */
//Форма данных  о пользователе

#ifndef _USERFORM_H
#define _USERFORM_H

#include "ui_userForm.h"
#include "User/User.h"
#include "Inspection/Inspection.h"

class userForm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit userForm(QWidget *parent = 0);
    ///деструктор
    virtual ~userForm();
    ///получить указатель на виджет окна
    Ui::userForm* getWidget();
    ///получить список инспекций
    const QList<Inspection>& getInspections() const;
    /// инициализировать список инспекций
    void setInspections(const QList<Inspection>&);
    /// преобразовать список  в Hash
    QHash <qint64, QString>  mapInspections();
private:
    ///указатель на виджет окна
    Ui::userForm* widget_;
    ///список инспекций
    QList<Inspection> inspections_;

};

#endif /* _USERFORM_H */
