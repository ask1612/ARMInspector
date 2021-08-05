/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DialogDestroyer.cpp
 * Author: kazun
 * 
 * Created on 26 апреля 2021 г., 22:09
 */


#include <QTimer>
#include "DialogDestroyer.h"

DialogDestroyer::DialogDestroyer() {

}

void DialogDestroyer::DelayedDestruction(QDialog* lDialog) {

    mDialog = lDialog;

    this->start();

}

void DialogDestroyer::run() {

    msleep(300);

    mDialog->deleteLater();
    this->deleteLater();
}

