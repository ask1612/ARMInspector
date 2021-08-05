/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   docsAP.h
 * Author: kazun_as
 *
 * Created on 30 июля 2021 г., 15:24
 */

#ifndef _DOCSAP_H
#define _DOCSAP_H

#include "ui_docsAP.h"
#include "QHBoxLayout"
#include "QHeaderView"
#include "QTableWidget"
class docsAP : public QDialog {
    Q_OBJECT
public:
    explicit docsAP(QWidget *parent = 0);
    virtual ~docsAP();
    ///Получить ссылку на виджет
    Ui::docsAP* getUI();
    void personView();


private:
    Ui::docsAP* widget_;
    QStringList m_TableHeader;
};

#endif /* _DOCSAP_H */
