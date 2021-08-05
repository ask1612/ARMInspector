/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 ** 
 **             ВЫВОД СПИСКА ПОЛЬЗОВАТЕЛЕЙ
 **             Класс окна вывода списка пользователя -Dialog.
 **             Используются для вывода данных о пользователе списком
 **             Модель вывода UserView.
 **
 ****************************************************************************/

/* 
 * File:   dialog.h
 * Author: kazun
 *
 * Created on 29 марта 2021 г., 20:44
 */


//Форма вывода списка пользователей

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QMessageBoxEx.h"

#include "ui_dialog.h"
#include "ClientController.h"
#include "Inspection/Inspection.h"
#include "User/User.h"
#include "userForm.h"
#include "userEditFrm.h"
#include "ModelList.h"
#include "User/UserView.h"
#include "pwdFrm.h"
#include <QSortFilterProxyModel>
#include "Functor.h"

class ClientController;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    ///Констуктор
    explicit Dialog(QWidget *parent = 0);
    //Деструктор
    ~Dialog();
    ///Получить ссылку на виджет
    Ui::dialog* getUI();

    ///вывести на экран  окно списка пользователей
    void showBox();
    ///показать отредактированные данные о  пользователе в  окне списка пользователей
    void showEditUserData(const User&);
    ///определить модель вывода данных
    void setModel(const QList<UserView>& nsi);
    //Показать новую добавленную запись в списке пользователей
    void showNewUserData(const User&);
    //Данные пользователя
    void fillUserEditFrm(const User& user);
    //установить список инспекций
    void setListInspections(const QList<Inspection>&);
private slots:
    ///обработчик кнопки добавления пользователя
    void on_pushButton_addUser_clicked();
    ///обработчик кнопки редактирования пользователя
    void on_pushButton_editUser_clicked();
    ///обработчик кнопки удаления  пользователя
    void on_pushButton_deleteUser_clicked();
    ///обработчик кнопки удаления  пользователя
    void on_pushButton_changePassword_clicked();
public slots:
    ///Обработчик команд (ответов) сервера
    void worker(const QString& asWrapper);

signals:
    ///Сигнализировать о завершении процесса обработки сообщения от сервера.
    void ready();
    ///Запросить данные у сервера
    void runServerCmd(const QString&);
    ///ждать ответ  сервера 
    void waitReady();

private:
    ///ссылка на виджет основного окна
    Ui::dialog *ui;
    ///ссылка на окно ввоода нового пользователя
    userForm *usrFrm_;
    ///ссылка на окно ввоода нового пароля
    pwdFrm *pwdFrm_;
    ///ссылка на окно релактирования выбранного пользователя
    userEditFrm *usrEdtFrm_;
    ///ссылка на модель  данных 
    ModelList<UserView>* listusers_;
    ///ссылк на экземпляр модели вывода данных
    UserView *userview_;
    ///модель сортировеки 
    QSortFilterProxyModel *proxyModel_;
    QString queryWrapper_;
    ///указатель контроллера клиента.
    ClientController *m_pClientController{nullptr};
};

#endif // DIALOG_H
