/****************************************************************************
 **
 **         Класс  Seance для организации сенса работы с базой данных.
 **
 ****************************************************************************/

/* 
 * File:   Seance.h
 * Author: kazun_as
 *
 * Created on 16 декабря 2019 г., 11:39
 */

#ifndef SEANCE_H
#define SEANCE_H
#include <QThread>
#include "Worker.h"
#include "Seance.h"

class Seance : public QObject {
    Q_OBJECT
public:
    /// Конструктор.
    Seance();
    /// Конструктор.
    /// @param asModelWrapper Данны, полученные от клиента,
    ///обёрнутые в командную оболочку и сериализованные в строку.  

    Seance(QString asModelWrapper);
    ///Деструктор.
    virtual ~Seance();
    //Список сеансов.
    static QVector<Seance*> m_aInstances;

    /// Создать новый поток.
    void addThread();
signals:
    //Сигнал   готовности данных;
    void onReadyResult(QString);

    public
Q_SLOTS:
    //
    void errorString(QString);
    static void handleResult(QString asQuery);


private:
    //Указатель на вспомогательный класс для работы с базой данных.
    // Worker * m_pWorker{nullptr};
    //Умный указатель на вспомогательный класс для работы с базой данных.
    std::unique_ptr<Worker> m_pWorker;
    //Указатель на поток.
    //QThread* m_pThread{nullptr};
    //Умный указатель на поток
    std::unique_ptr<QThread> m_pThread;
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;


};

#endif /* SEANCE_H */

