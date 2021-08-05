/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myThread.h
 * Author: kazun
 *
 * Created on 26 июля 2021 г., 21:41
 */

#ifndef MYTHREAD_H
#define MYTHREAD_H
#include "DBManager.h"
#include "ModelWrapper.h"

class myThread : public QRunnable {
public:
    myThread();
    myThread(const myThread& orig);
    virtual ~myThread();
    /// Инициализировать строку командной обёртки.
    /// @param asWrapperString Строка инициализации командной обёртки
    void setModelWrapperString(const QString& asWrapperString);

    void run();
private:
    static QMutex mutex_;
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;
    DBManager *m_pDBManager;


};

#endif /* MYTHREAD_H */

