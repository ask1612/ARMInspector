/****************************************************************************
 **
 **            ОБРАБОТЧИК СООБЩЕНИЙ СЕРВЕРА
 **            Класс обработки сообщений от сервера. 
 **            Обрабатывает сообщения от сервера  и передает управление
 **            с помощью сигнально-слотового соединения контоллеру клиента или  
 **            новому окну ввода данных или окну сообщения или вызывает 
 **            дополнительные модули обработки данных.
 **             
 **
 ****************************************************************************/

/* 
 * File:   WorkerClient.h
 * Author: ASK
 *
 * Created on 14 декабря 2019 г., 19:50
 */

#ifndef WORKERCLIENT_H
#define WORKERCLIENT_H
#include <QtCore>
#include "ModelWrapper.h"
#include "JsonSerializer.h"
#include "ItemContainer.h"
#include "ModelList.h"
#include "User/User.h"
#include "Mro/Mro.h"
#include "User/UserView.h"
#include "Inspection/Inspection.h"
#include "User/dialog.h"
#include "RptColumn/RptColumnFrm.h"
#include "Nsi/nsiFrm.h"
#include "QMessageBoxEx.h"

class WorkerClient : public QObject {
    Q_OBJECT

public:
    QList<Inspection> inspections_;
    /// Стандартный конструктор.
    /// @param apParent Родитель.
    WorkerClient(QObject *apParent = nullptr);
    /// Стандартный конструктор.
    ~WorkerClient();
    void setModelWrapperString(const QString& asWrapperString);
    const QString& getModelWrapperString() const;
    ///Основная функция потока
    void process();


signals:
    ///выполнить команду на сервере
    void runServerCmd(const QString&);
    ///получен ответ сервера
    void responseServer(const QString&);

    ///Установить идентификатор клиента
    void setID(int asID);
    ///Установить сессионого пользователя
    void setSessionUser(const User&);
    ///Ждать ответ сервера
    void waitReady();
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();
    ///Передать список инспекций
    void passListInspections(const QList<Inspection>& inspections);
    ///Получить  данные о пользователе
    void getUserData(const qint64&);
    ///Удалить  данные о пользователе
    void deleteUser(const qint64&);
    ///Cписок инспекций подготовлен  
    void listInspectionsReady(const QList<Inspection>&);
    ///Cписок НСИ подготовлен  
    void listNsiReady(const QList<Nsi>&);
    ///Cписок пользователей подготовлен  
    void listUserReady(const QList<UserView>&);
    ///Данные пользователя   
    void userReady(const User&);
    ///Данные НСИ  
    void nsiReady(const Nsi&);
    ///Cписок МРО подготовлен  
    void listMroReady(const QList<Mro>&);
    ///Сигнал завершения работы.
    /// @param asResult Результат выполнения запроса 
    void finished(QString asResult);
    void error(QString asError);
private:
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;
    //reportFrm* reportDlg_;
};

#endif /* WORKERCLIENT_H */

