/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainWindow.h
 * Author: kazun_as
 *
 * Created on 5 февраля 2021 г., 10:26
 */

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H
#include "ClientController.h"
#include <QMessageBox>
#include "ModelWrapper.h"

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
    void initClient(ClientController *clientController);
    ///создать сигнально-слотовые соединения
    ///между основноё формой и формой ввода-редактирования 
    void createUserConnector(const Dialog& frm);
signals:
    ///Запросить данные у сервера
    void runServerCmd(const QString&);
    ///сигнал завершения операции и готовности
    ///к выполнению следующей операций
    void ready();
    ///ждать ответ  сервера 
    void waitReady();
    ///ответ сервера
    void responseServer(const QString&);

private slots:
    void ListUsers();
    void OnExit();

private:
    Ui::MainWindow widget;
    ///Контроллер клиента.
    ClientController *m_pClientController{nullptr};
};


#endif /* _MAINWINDOW_H */
