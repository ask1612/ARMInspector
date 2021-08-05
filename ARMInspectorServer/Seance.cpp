/****************************************************************************
 **
 **         Реализация методов класса  Seance.
 **
 ****************************************************************************/

/* 
 * File:   Seance.cpp
 * Author: kazun_as
 * 
 * Created on 16 декабря 2019 г., 11:39
 */

#include "Seance.h"
#include "myThread.h"
#include <QDebug>
#include "Session.h"

///Список сеансов.
QVector<Seance*> Seance::m_aInstances;
/// Конструктор.
/// @param asModelWrapper Данны, полученные от клиента,
///обёрнутые в командную оболочку и сериализованные в строку.  

Seance::Seance(QString asModelWrapper) {
    //Сохранить указатель на экземпляр класса Seance в списке.
    m_aInstances.push_back(this);
    //Записать данные.
    m_aModelWrapperString = asModelWrapper;
}

///Деструктор.

Seance::~Seance() {
    //m_pWorker->getDBManager()->removeDatabase();
    ///Искать сеанс в списке.
    QVector<Seance*>::iterator p = std::find(m_aInstances.begin(), m_aInstances.end(), this);
    ///Если сеанс найдена, убрать его из списка.
    if (p != m_aInstances.end()) {
        m_aInstances.erase(p);
    }
    //Удалить поток.
    if (m_pThread != nullptr) {
        qDebug() << "Stop Thread";
        m_pThread->quit();
        m_pThread->wait();
    }
}


/// Создать новый поток.

void Seance::addThread() {
    //Создать  командную обёртку. 
    //ModelWrapper wrapper;
    // Конвертировать данные, пришедшие от клиента в JSON объект.
    //JsonSerializer::parse(m_aModelWrapperString, wrapper);
    QThreadPool *thread_pool = QThreadPool::globalInstance();
    //if (thread_pool->waitForDone()) {
    myThread *thread = new myThread();
    thread->setAutoDelete(true);
    thread->setModelWrapperString(m_aModelWrapperString);
    thread_pool->start(thread);
    //}
}

/// Обработать возвращённый результат  запроса.
/// @param asQuery возвращенные Worker. 

void Seance::handleResult(QString asQuery) {
    //Создать  командную обёртку. 

    //Сигнализировать  сессии, что обработка запроса завершена;
    Session::handleRes(asQuery);
    //emit onReadyResult(asQuery);
}


///Сообщение об ошибке при работе с потоками.
/// @param asError Ошибка апри работе с потоками.

void Seance::errorString(QString asError) {

    qCritical() << QString("addThread FAILURE:  %s").arg(asError);

}
