/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptRowFrm.h
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 14:45
 */

#ifndef _RPTROWFRM_H
#define _RPTROWFRM_H
#include "ui_RptRowFrm.h"
#include "RptRow/RptRow.h"
#include "RptRow/RptRowEditForm.h"
#include "ModelList.h"
#include "Functor.h"
#include "MQuery.h"
#include "QMessageBoxEx.h"

class RptRowEditForm;

class RptRowFrm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit RptRowFrm(QWidget *parent = 0);
    ~RptRowFrm();
    ///Получить ссылку на виджет
    Ui::RptRowFrm* getUI();
    ///Установить размер таблицы
    void setSizeTbl(const int& width, const int& height);
    ///определить модель вывода данных
    void setModel(const QList<RptRow>&);
    ///показать данные МРО
    void showData(const RptRow&);
    ///показать отредактированные данные 
    void showEditData(const RptRow&);
    //Данные 
    void fillEditFrm(const RptRow&);

private slots:
    ///обработчик кнопки добавления записи НСИ
    void on_pushButton_Add_clicked();
    ///обработчик кнопки редактирования записи НСИ
    void on_pushButton_Edit_clicked();
    ///обработчик кнопки удаления  записи НСИ
    void on_pushButton_Remove_clicked();

    ///Обработчик команд (ответов) сервера
    void worker(const QString&);

signals:
    void ready();
    ///Запросить данные у сервера
    void runServerCmd(const QString&);
    ///сигнализировать  о  необходимости  ожидания ответа от сервера 
    void waitReady();
private:
    Ui::RptRowFrm *widget_;
    ///ссылка на модель  данных 
    ModelList<RptRow>* listrptrow_;
    ///ссылк на экземпляр модели вывода данных
    RptRow *rptrow_;
    ///ссылка на окно ввоода новой записи
    RptRowEditForm *rptrowEditFrm_;

    ///модель сортировеки 
    QSortFilterProxyModel *proxyModel_;
};

#endif /* _RPTCOLUMNFRM_H */
