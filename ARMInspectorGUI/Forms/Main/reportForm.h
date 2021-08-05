/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reportForm.h
 * Author: kazun_as
 *
 * Created on 16 апреля 2021 г., 13:09
 */

#ifndef _reportForm_H
#define _reportForm_H

#include "ui_reportForm.h"
#include <QMenuBar>
#include <QMainWindow>
#include <QTableView>
#include <QModelIndex>
#include <QStandardItemModel>
#include "ClientController.h"
#include "Report/Report.h"
#include "ContextData/ContextData.h"
#include "Mro/Mro.h"
#include "Mro/mroFrm.h"
#include "Nsi/nsiFrm.h"
#include "RptRow/RptRowFrm.h"
#include "DialogDestroyer.h"
#include "Inspection/inspectionFrm.h"
#include <array>

#define TAB_VIEW 4

class reportForm : public QMainWindow {
    Q_OBJECT
public:
    reportForm();
    virtual ~reportForm();
    ///Инициализация ссылки на контроллер клинта
    void initClient(ClientController *clientController);
    ///Скрыть элементы управления 
    void hideControlsFrm();
    ///Показать элементы управления 
    void showControlsFrm();
    ///Сформировать отчёт
    void report(int);
    ///Объединить ячейки таблицы
    void spanTbl(int);
    ///Получить указатель на меню
    QMenuBar * getMenuBar();
    ///Меню.Сформировать отчёт
    void OnGenerateReport();
    ///Меню.Выйти из программы 
    void OnExit();
    ///Меню.Сформировать отчёт.Приложение 2
    void OnGenerateReprt2();
    ///Меню. Управление справочником инспекций. 
    void OnInspection();
    ///Меню. Управление справочником МРО
    void OnMro();
    ///Меню. Управление справочником стаьей КоАП
    void OnArticle();
    ///Меню. Управление справочником  субъектов АП
    void OnSubject();
    ///Меню. Управление справочником  колонок отчёта 
    void OnRptColumn();
    ///Меню. Управление справочником  строк отчёта 
    void OnRptRow();
    ///создать сигнально-слотовые соединения
    ///между основноё формой и формой ввода-редактирования 
    void createFrmConnector(const QDialog&);
    //инициализировать список МРО;
    void setlistMro(const QList<Mro>&);
    //инициализироваь список строк отчёта;
    void setlistRow(const QList<RptRow>&);
    //инициализировать список колонок отчёта;
    void setlistCol(const QList<RptColumn>&);
    //инициализировать список результата полученного от сервера;
    void setlistResult(const QList<ReportOut>&);
    void setContextResult(const QList<ContextOut>&);
    //сбросить флаги заполнености талиц;
    void resetTabs();
    //Получить флаги заполнености талиц;
    const array<bool, TAB_VIEW>& getTabs();
    //Установить  флаг заполнености талиц;
    void setTab(const int&, const bool&);
    //Получить флаг заполнености талиц;
    const bool& getTab(const int&);
    //Установить стиль таблицы;
    void setTableStyle(QTableView*);
    void initTblView();
    //Установить пользователя
     void setUser(const User&);
    //Получить пользователя
    const User& getUser() const;
    //Установить строку периода
    void setPeriod();
    //Установить индикатор нарастающего итога
    void setCummulative();
    //Получить  строку периода
    const QString& getPeriod() const;
    //Получить  индикатор нарастающего итога
    const qint64& getCummulative() const;
    void setMenuByUserRole();

signals:
    ///сигнал готовности
    void ready();
    ///Ждать ответ сервера
    void waitReady();
    ///Запросить данные у сервера
    void runServerCmd(const QString&);
    ///Ответ сервера
    void responseServer(const QString&);
    ///список НСИ подготовлен    
    void listNsiReady(const QList<Nsi>&);
    ///запись НСИ подготовлена    
    void nsiReady(const Nsi&);

private slots:
    void onTableClicked(const QModelIndex &);
    void on_pushButton_Report_clicked();
    //void on_pushButton_Excel_clicked();
    void tabSelected();
    void showButtons();
    void hideButtons();
    ///Обработчик команд (ответов) сервера
    void worker(const QString& asWrapper);

    static array<QString, TAB_VIEW> getListExcelFiles() {
        return array<QString, TAB_VIEW>{
            "test4.csv",
            "test1.csv",
            "test2.csv",
            "test3.csv"};
    }

    static array<QString, TAB_VIEW> getListMroName() {
        return array<QString, TAB_VIEW>{
            "Филиал",
            "Брест",
            "Барановичи",
            "Пинск"};
    }

    static array<QString, TAB_VIEW> getListMroNameInReport() {
        return array<QString, TAB_VIEW>{
            "по филиалу Госэнергогазнадзора по Брестской области ",
            "по Брестскому межрайонному отделению ",
            "по Барановичскому межрайонному отделению ",
            "по Пинскому межрайонному отделению "};
    }


private:
    Ui::reportForm widget;
    QMenuBar * m_pMenuBar;
    QMenu * m_pMenu;
    array<QStandardItemModel, TAB_VIEW> model_;
    ///список МРО
    QList<Mro> mro_;
    ///список строк отчёта
    QList<RptRow> listrow_;
    ///список колонок  отчёта
    QList<RptColumn> listcol_;
    ///указатель контроллера клиента.
    ClientController *m_pClientController{nullptr};
    //nsiFrm* frm; 
    QList<ReportOut> result_;
    QList<ContextOut> contextresult_;
    bool pressed_{false};
    array<QTableView*, TAB_VIEW> tblview_;
    array<bool, TAB_VIEW> tab_{
        false,
        false,
        false,
        false};
    //Период отчёта    
    QString prd_;
    //Индикатор нарастающего итога
    qint64 cummulative_;
    //пользователь
    User user_;
};

#endif /* _reportForm_H */
