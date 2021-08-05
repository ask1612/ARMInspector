/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 ** 
 **             АВТОРИЗАЦИЯ ПОЛЬЗОВАТЕЛЯ
 **             Класс окна авторизации  пользователя -myForm.
 **
 **
 ****************************************************************************/

/* 
 * File:   myForm.h
 * Author: kazun_as
 *
 * Created on 2 февраля 2021 г., 10:31
 */

//Форма аутентификации пользавателя

#ifndef _MYFORM_H
#define _MYFORM_H

#include "ui_myForm.h"
#include "ClientController.h"
#include "ModelWrapper.h"
#include "Functor.h"
#include <QCloseEvent>

class myForm : public QDialog {
    Q_OBJECT
public:
    //конструктор
    explicit myForm(QWidget *parent = 0);
    //деструктор
    virtual ~myForm();
    ///Инициализация ссылки на контроллер клинта
    void initClient(ClientController *clientController);
    ///Инициализация приложения
    void initApp(QApplication *app);
    ///Обработчик события закрытия окна
    void closeEvent(QCloseEvent* ev);
public slots:
    ///Закрытие приложения
    void exit_app();
    ///Запуск АРМ Инспектора
    void start_ARM();
signals:
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();
private:
    ///ссылка на виджет окна
    Ui::myForm *widget;
    ///указатель контроллера клиента.
    ClientController *m_pClientController{nullptr};
    //QApplication *m_pApp;
};

#endif /* _MYFORM_H */
