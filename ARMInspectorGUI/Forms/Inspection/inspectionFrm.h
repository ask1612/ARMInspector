/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   inspectionFrm.h
 * Author: kazun_as
 *
 * Created on 14 мая 2021 г., 15:40
 */

#ifndef _INSPECTIONFRM_H
#define _INSPECTIONFRM_H

#include "ui_inspectionFrm.h"
#include "Inspection/Inspection.h"
#include "Inspection/InspectionView.h"
#include "ModelList.h"
#include "Functor.h"
#include "MQuery.h"
#include "QMessageBoxEx.h"
#include "inspectionEditForm.h"
class inspectionFrm : public QDialog {
     Q_OBJECT
public:
    ///конструктор
    explicit inspectionFrm(QWidget *parent = 0);
    ~inspectionFrm();
    ///Получить ссылку на виджет
    Ui::inspectionFrm* getUI();
    ///Установить размер таблицы
    void setSizeTbl(const int& width, const int& height);
    ///определить модель вывода данных
    void setModel(const QList<InspectionView>& mro);
    ///показать данные МРО
    void showData(const Inspection& );
    ///показать отредактированные данные 
    void showEditData(const Inspection&);
    //установить список инспекций
    void setListMro(const QList<Mro>&);
    //Данные МРО
    void fillEditFrm(const Inspection& inspection);

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
    Ui::inspectionFrm *widget_;
    ///ссылка на модель  данных 
    ModelList<InspectionView>* listinspection_;
    ///ссылк на экземпляр модели вывода данных
    InspectionView *inspectionview_;
    ///ссылка на окно ввоода новой записи
    inspectionEditForm *inspectionEditFrm_;

    ///модель сортировеки 
    QSortFilterProxyModel *proxyModel_;

};

#endif /* _INSPECTIONFRM_H */
