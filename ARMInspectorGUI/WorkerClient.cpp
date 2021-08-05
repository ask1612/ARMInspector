/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 **
 **            ОБРАБОТЧИК СООБЩЕНИЙ СЕРВЕРА 
 **            Класс обработки сообщений  сервера. 
 **            Обрабатывает сообщения от сервера  и передает управление
 **            с помощью сигнально-слотового соединения контоллеру клиента или  
 **            новому окну ввода данных или окну сообщения или вызывает 
 **            дополнительные модули обработки данных.
 **             
 **
 ****************************************************************************/


/* 
 * File:   WorkerClient.cpp
 * Author: ASK
 * 
 * Created on 14 декабря 2019 г., 19:50
 */

#include "WorkerClient.h"
#include "QMessageBoxEx.h"
#include <QTableView>
#include "User/dialog.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

WorkerClient::WorkerClient(QObject *apParent) : QObject(apParent) {
}

///-----------------------------------------------------------------------------
///
///         Деструктор
///          
///-----------------------------------------------------------------------------

WorkerClient::~WorkerClient() {
    //Освободить  ресурсы

}

///-----------------------------------------------------------------------------
///
///            Инициализировать строку командной обёртки.
///            @param asWrapperString Строка инициализации командной обёртки
///          
///-----------------------------------------------------------------------------

void WorkerClient::setModelWrapperString(const QString& asWrapperString) {

    m_aModelWrapperString = asWrapperString;
}

///-----------------------------------------------------------------------------
///
///          Получить строку командной обёртки.
///          @return Возвращает строку командной обёртки.
///          
///-----------------------------------------------------------------------------

const QString& WorkerClient::getModelWrapperString() const {

    return m_aModelWrapperString;
}



///-----------------------------------------------------------------------------
///
///         Основная функция обработчики сообщений, полученных от сервера.
///          
///-----------------------------------------------------------------------------

void WorkerClient::process() {
    //QMessageBox::information(0, "Добавление нового пользовтеля", "Пользователь успешно добавлен в базу данных");
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(m_aModelWrapperString, wrapper);
    //Вывести заголовок и сообщение.
    ////qInfo() << "head: " << QString::fromLocal8Bit(wrapper.getHead().toStdString().c_str());
    ////qInfo() << "message: " << QString::fromLocal8Bit(wrapper.getMessage().toStdString().c_str());
    //Проверяем результат выполнения команды 
    ModelWrapper::Command command = wrapper.getEnumCommand();
    ModelWrapper::Model model = wrapper.getEnumModel();
    QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
    QMessageBoxEx::setCustomTextForButton(QMessageBox::No, "Нет");
    if (wrapper.getSuccess()) {
        //*******************************************************************************************************************************************
        //                                  Команда на сервере выполнена успешно.
        //*******************************************************************************************************************************************
        switch (command) {
            case ModelWrapper::Command::SET_SESSION_ID:
            {
                ///Сообщить контроллеру клиента о небходимости
                //установить ID сессии
                //QMessageBox::information(0, "Menu", QString::number(wrapper.getSessionID()));
                emit setID(wrapper.getSessionID());
            }
                break;
            case ModelWrapper::Command::ADD_CONNECTION:
            {
                emit ready();
            }
                break;
            case ModelWrapper::Command::LOGIN:
            {
                //Сервер вернул результат команды "LOGIN"     
                User user;
                JsonSerializer::parse(wrapper.getData(), user);
                emit setSessionUser(user);
                //MessageBox::information(0, "LOGIN",
                //        "User with name " + user.getName().trimmed() + " is logged in");
                //qInfo() << "User with name " << user.getName().trimmed() << " is logged in";
                //Сигнализировать о завершении обработки.
                emit ready();
            }
                break;
            case ModelWrapper::Command::NOP:
            {
                //qInfo() << "Command is incorrect";

            }
                break;
            case ModelWrapper::Command::SERVER_RESPONSE:
            {

                //qInfo() << "Уведомление от сервера";

            }
                break;
            case ModelWrapper::Command::GET_LIST_MODELS:
            case ModelWrapper::Command::ADD_NEW_USER:
            case ModelWrapper::Command::EDIT_USER:
            case ModelWrapper::Command::CHANGE_PASSWORD:
            case ModelWrapper::Command::GET_MODEL:
            case ModelWrapper::Command::ADD_NEW_MODEL:
            case ModelWrapper::Command::UPDATE_MODEL:
            case ModelWrapper::Command::DEL_MODEL:
            case ModelWrapper::Command::CALL_PROCEDURE:
                emit responseServer(m_aModelWrapperString);
                break;
            default:
                break;
        }
    } else {
        //*******************************************************************************************************************************************
        //                                  Ошибка выполнения команды на сервере.
        //*******************************************************************************************************************************************
        QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
        QMessageBoxEx::critical(Q_NULLPTR, wrapper.getHead(), wrapper.getMessage());
    }
}



