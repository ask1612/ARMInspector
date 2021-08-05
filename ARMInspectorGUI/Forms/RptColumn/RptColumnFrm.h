/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RptColumnFrm.h
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 14:45
 */

#ifndef _RPTCOLUMNFRM_H
#define _RPTCOLUMNFRM_H
#include "ui_RptColumnFrm.h"
#include "RptColumn/RptColumn.h"
#include "RptColumn/RptColumnView.h"
#include "RptColumn/RptColumnEditForm.h"
#include "ModelList.h"
#include "Functor.h"
#include "MQuery.h"
#include "QMessageBoxEx.h"


class RptColumnFrm : public QDialog {
    Q_OBJECT
public:
    ///конструктор
    explicit RptColumnFrm(QWidget *parent = 0);
    ~RptColumnFrm();
    ///Получить ссылку на виджет
    Ui::RptColumnFrm* getUI();
    ///Установить размер таблицы
    void setSizeTbl(const int& width, const int& height);
    ///определить модель вывода данных
    void setModel(const QList<RptColumnView>& );
    ///показать данные МРО
    void showData(const RptColumn& );
    ///показать отредактированные данные 
    void showEditData(const RptColumn&);
    //установить список инспекций
    void setListNsi(const QList<Nsi>&);
    //Данные 
    void fillEditFrm(const RptColumn&);

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
    Ui::RptColumnFrm *widget_;
    ///ссылка на модель  данных 
    ModelList<RptColumnView>* listrptcolumnview_;
    ///ссылк на экземпляр модели вывода данных
    RptColumnView *rptcolumnview_;
    ///ссылка на окно ввоода новой записи
    RptColumnEditForm *rptcolumnEditFrm_;

    ///модель сортировеки 
    QSortFilterProxyModel *proxyModel_;
};

#endif /* _RPTCOLUMNFRM_H */
