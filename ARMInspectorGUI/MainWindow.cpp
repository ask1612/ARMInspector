/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MainWindow.cpp
 * Author: kazun_as
 *
 * Created on 5 февраля 2021 г., 10:26
 */

#include "MainWindow.h"
#include <QStandardItemModel>
#include <QScrollBar>
#include "Functor.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
    connect(this->widget.actionListUsers, SIGNAL(triggered()), this, SLOT(ListUsers()));
    connect(this->widget.actionExit, SIGNAL(triggered()), this, SLOT(OnExit()));
}

MainWindow::~MainWindow() {
}



///-----------------------------------------------------------------------------
///
///         Список пользователей.
///          
///-----------------------------------------------------------------------------

void MainWindow::ListUsers() {
    //QMessageBox::information(0, "АРМ Администратора", "Список пользователей");
    //m_pClientController->getListModels(ModelWrapper::Model::UserView);
    Dialog* frm = new Dialog();
    createUserConnector(*frm);
    QJsonObject param;
    emit runServerCmd(Functor<UserView>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    emit runServerCmd(Functor<Inspection>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->showBox();
    //delete frm;
}

///-----------------------------------------------------------------------------
///
///         сигнально-слотовое соединение MainWindow<---->Dialog
///          
///-----------------------------------------------------------------------------

void MainWindow::createUserConnector(const Dialog& frm) {
    ///выполнить команду на сервере
    connect(&frm, SIGNAL(runServerCmd(const QString&)), this, SIGNAL(runServerCmd(const QString&)));
    ///получен ответ от сервера в виде строки
    connect(this, SIGNAL(responseServer(const QString&)), &frm, SLOT(worker(const QString&)));
    // Сигнально - слотовое соединение ожидания ответа от сервера.
    connect(&frm, SIGNAL(waitReady()), this, SIGNAL(waitReady()));
    ///сигнал завершения процесса обработки
    connect(&frm, SIGNAL(ready()), this, SIGNAL(ready()));

}

///-----------------------------------------------------------------------------
///
///         initClient
///          
///-----------------------------------------------------------------------------

void MainWindow::initClient(ClientController * clientController) {
    m_pClientController = clientController;
    ///сигнал завершения процесса обработки
    connect(this, SIGNAL(ready()), m_pClientController, SLOT(formReady()));
    // Сигнально - слотовое соединение ожидания ответа от сервера.
    connect(this, SIGNAL(waitReady()), m_pClientController, SLOT(waitReady()));
    ///выполнить команду на сервере
    connect(this, SIGNAL(runServerCmd(const QString&)), m_pClientController,
            SLOT(runServerCmd(const QString&)));
    ///получен ответ от сервера в виде строки
    connect(m_pClientController, SIGNAL(responseServer(const QString&)),
            this, SIGNAL(responseServer(const QString&)));

};



///-----------------------------------------------------------------------------
///
///         Список пользователей.
///          
///-----------------------------------------------------------------------------

void MainWindow::OnExit() {
    //QMessageBox::information(0, "АРМ Администратора", "Список пользователей");
    QMessageBoxEx::StandardButton reply;
    reply = QMessageBoxEx::question(this, "Завершение работы АРМ Инспектор",
            "Вы действительно хотите завершить работу ? ",
            QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        qApp->quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}





