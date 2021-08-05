/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DialogDestroyer.h
 * Author: kazun
 *
 * Created on 26 апреля 2021 г., 22:09
 */

#ifndef DIALOGDESTROYER_H
#define DIALOGDESTROYER_H

#include <QThread>
#include <QDialog>
 
class DialogDestroyer : public QThread
{
public:
	DialogDestroyer();
 
	void DelayedDestruction(QDialog* lDialog);
 
private:
	void run();
 
	QDialog* mDialog;
};

#endif /* DIALOGDESTROYER_H */

