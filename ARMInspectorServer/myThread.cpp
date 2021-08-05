/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myThread.cpp
 * Author: kazun
 * 
 * Created on 26 июля 2021 г., 21:41
 */

#include "myThread.h"
#include "User/User.h"
#include <QScopedPointer>
#include "Seance.h"
QMutex myThread::mutex_;

myThread::myThread() {
}

myThread::myThread(const myThread& orig) {
}

myThread::~myThread() {
}
/// Инициализировать строку командной обёртки.
/// @param asWrapperString Строка инициализации командной обёртки

void myThread::setModelWrapperString(const QString& asWrapperString) {
    m_aModelWrapperString = asWrapperString;
}

///Основная функция  потока, который создаётся в сеансе.
///Создает экземпляр класса управления базой данных DBManager.
///Прозводит обработку  данных, пришедших от клиента.
///Возвращает результат обработки данных.
///Все действия производятся через командную обёртку.

void myThread::run() {
    //QMutexLocker lock(&myThread::mutex_);
    //QThreadPool *thread_pool = QThreadPool::globalInstance();
    //thread_pool->waitForDone(1000);
    //Создать  командную обёртку. 
    ModelWrapper wrapper;
    //Задать  функцию для установки результата выполнения команды сервера
    //и собщения о результате выполнения команды.
    auto setResult = [ &wrapper](Message msg) {
        //Установить сообщение и результат выполнения команды.
        ServerMessage::Result result = ServerMessage::outPut(msg);
        wrapper.setMessage(result.str);
        wrapper.setSuccess(result.success);
    };
    //Создать экземпляр класса управления базой данных.
    DBManager *pDBManager = new DBManager();
    //QScopedPointer<DBManager> m_pDBManager(new DBManager());
    //connect(m_pDBManager, SIGNAL(finished(QString)), SIGNAL(finished(QString)));

    if (pDBManager != nullptr) {
        //myThread::mutex_.lock();
        //Создать соединение, которое обработает возвращенный результат. 
        //Экземпляр класса управления базой данных создан успешно.
        //Конвертировать данные, пришедшие  от клиента в JSON объект.
        JsonSerializer::parse(m_aModelWrapperString, wrapper);
        //Читать команду, которую  необходимо выполнить на сервере.
        ModelWrapper::Command command = wrapper.getEnumCommand();
        ///Передать данные DBManager.
        pDBManager->setModelWrapper(&wrapper);
        //Подключаемся к базе данных.
        bool ok = pDBManager->addDataBase();
        if (ok) {
            qDebug() << "database work  is running!!! ";

            //Подключение к базе данных успешно добавлено.
            //Выбрать команду, которую нужно выполнить. 
            switch (command) {
                case ModelWrapper::Command::LOGIN:
                {
                    //Авторизация.
                    pDBManager->login();
                }
                    break;
                case ModelWrapper::Command::ADD_NEW_USER:
                {
                    //Добавление нового пользователя .
                    pDBManager->addUser();
                }
                    break;
                case ModelWrapper::Command::ADD_NEW_MODEL:
                {
                    //Добавление новой  записи .

                    pDBManager->addModel();
                }
                    break;
                case ModelWrapper::Command::EDIT_USER:
                {
                    //Добавление нового пользователя .
                    pDBManager->updateUser();
                }
                    break;
                case ModelWrapper::Command::CHANGE_PASSWORD:
                {
                    //Добавление нового пользователя .
                    pDBManager->changePassword();
                }
                    break;
                case ModelWrapper::Command::GET_LIST_MODELS:
                {
                    //Получить список моделей.
                    pDBManager->getListModels();
                }
                    break;
                case ModelWrapper::Command::GET_MODEL:
                {
                    //Получить список моделей.
                    pDBManager->getModel();
                }
                    break;
                case ModelWrapper::Command::UPDATE_MODEL:
                {
                    //Редактировать модель.
                    pDBManager->updateModel();
                }
                    break;
                case ModelWrapper::Command::DEL_MODEL:
                {
                    //Удалить модель.
                    pDBManager->deleteModel();
                }
                    break;
                case ModelWrapper::Command::CALL_PROCEDURE:
                {
                    //Вызвать хранимую процедуру.
                    pDBManager->callProcedure();
                }
                    break;
                default:
                {
                    setResult(Message::INCORRECT_COMMAND);
                }
                    break;
            }
            ///Удаляем подключение  к базе данных.
            //pDBManager->removeDatabase();
        }
        //Удалить экземпляр класса управления базой данных.
        delete pDBManager;
        //myThread::mutex_.unlock();
    } else {
        //Не удалось создать экземпляр класса  управления базой данных.
        setResult(Message::FAILED_CREATE_DBMANAGER);
    }
    //Сериализовать  результат.
    m_aModelWrapperString = JsonSerializer::serialize(wrapper);
    //Сигнализировать о завершении  обработки информации.
    //emit finished(m_aModelWrapperString);
    Seance::handleResult(m_aModelWrapperString);

}
