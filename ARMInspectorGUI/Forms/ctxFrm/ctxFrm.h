/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ctxFrm.h
 * Author: kazun_as
 *
 * Created on 30 июля 2021 г., 09:50
 */

#ifndef _CTXFRM_H
#define _CTXFRM_H

#include "ui_ctxFrm.h"
#include "ContextData/ContextData.h"
class ctxFrm : public QDialog {
    Q_OBJECT
public:
    explicit ctxFrm(QWidget *parent = 0);
    virtual ~ctxFrm();
    ///Получить ссылку на виджет
    Ui::ctxFrm* getUI();
    //Вывести данные на экран
    void displayTable(const QList<ContextOut>&);
private slots:
    void onTableClicked(const QModelIndex &);
private:
    Ui::ctxFrm *widget_;
    QList<ContextOut> contextresult_;
};

#endif /* _CTXFRM_H */
