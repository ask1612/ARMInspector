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
 * File:   myForm.cpp
 * Author: kazun_as
 *
 * Created on 2 февраля 2021 г., 10:31
 */

#include "myForm.h"
#include <QMessageBox>

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

myForm::myForm(QWidget *parent) :
QDialog(parent), widget(new Ui::myForm) {
    widget->setupUi(this);
    //widget.setupUi(this);
    connect(widget->okButton, SIGNAL(clicked()), this, SLOT(start_ARM()));
    connect(widget->cancelButton, SIGNAL(clicked()), this, SLOT(exit_app()));
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

myForm::~myForm() {
    delete widget;
}
///-----------------------------------------------------------------------------
///
///         Обработчик закрытия окна.
///          
///-----------------------------------------------------------------------------

void myForm::closeEvent(QCloseEvent* ev) {
    qApp->quit();

}
///-----------------------------------------------------------------------------
///
///         Закрытие приложения.
///          
///-----------------------------------------------------------------------------

void myForm::exit_app() {
    qApp->quit();
}

///-----------------------------------------------------------------------------
///
///         Запуск АРМ Инспектора.
///          
///-----------------------------------------------------------------------------

void myForm::start_ARM() {
    QJsonObject param;
    param.insert("name", this->widget->nameEdit->text());
    param.insert("password", this->widget->passEdit->text());
    m_pClientController->runServerCmd(Functor<User>::producePrm(ModelWrapper::Command::LOGIN,param));
}

///-----------------------------------------------------------------------------
///
///         Инициализация ссылки на контроллер клиента.
///          
///-----------------------------------------------------------------------------

void myForm::initClient(ClientController *clientController) {
    m_pClientController = clientController;
    // Сигнально-слотовое соединение, сигнализирующее, что   контроллер комманд
    // готов вернуть  результат  выполнения запроса к серверу.
    connect(this, SIGNAL(ready()), m_pClientController, SLOT(formReady()));

};

