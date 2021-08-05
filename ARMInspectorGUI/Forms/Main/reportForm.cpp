/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   reportForm.cpp
 * Author: kazun_as
 *
 * Created on 16 апреля 2021 г., 13:09
 */

#include "reportForm.h"
#include "myProgressBar.h"
#include "QMessageBoxEx.h"
#include "ctxFrm/ctxFrm.h"
#include <QFile>
#include <QTextStream>
#include <QLayout>
#include <QProgressBar>
#include <QtCore/QCoreApplication>
//#include <ActiveQt/QAxWidget>
//#include <ActiveQt/QAxBase>
//#include <ActiveQt/QAxObject>
#include <array>
// [0] include QXlsx headers 
//#include "xlsxdocument.h"
//#include "xlsxchartsheet.h"
//#include "xlsxcellrange.h"
//#include "xlsxchart.h"
//#include "xlsxrichstring.h"
//#include "xlsxworkbook.h"
//using namespace QXlsx;

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

reportForm::reportForm() {

    widget.setupUi(this);
    //model_ = new QStandardItemModel;
    m_pMenuBar = new QMenuBar(this);
    //frm = new nsiFrm(this);
    this->setMenuBar(m_pMenuBar);
    QMenu * menu1 = m_pMenuBar->addMenu("&Журнал");
    // Выход
    QAction * action = new QAction("&Выход", this);
    connect(action, &QAction::triggered, this, &reportForm::OnExit);
    menu1->addAction(action);
    QMenu * menu = m_pMenuBar->addMenu("&Отчеты по АП");
    //menu->setLayoutDirection(Qt::RightToLeft); // Display menu bar to the right
    // New
    action = new QAction("&Отчёт Приложение 1", this);
    action->setIcon(QPixmap("Icons/icons8-file-48.png"));
    connect(action, &QAction::triggered, this, &reportForm::OnGenerateReport);
    menu->addAction(action);
    // Open
    action = new QAction("&Отчёт Приложение 2", this);
    connect(action, &QAction::triggered, this, &reportForm::OnGenerateReprt2);
    menu->addAction(action);

    //qApp->setStyleSheet("QMainWindow { background-color: yellow; border: 1px solid #424242 }"
    //        "QLCDNumber { background-color: red }"
    //        "QMenu::separator{height: 2px; background: lightblue; margin-left: 10px; margin-right: 5px;}"
    //        "QMenu::indicator { width: 13px; height: 13px; }"
    //        "QMenuBar::item { spacing: 3px;  padding: 1px 4px; background: transparent; border-radius: 4px; }"
    //        "QMenuBar::item:selected {background: #a8a8a8;}"
    //        "QMenuBar::item:pressed { background: #888888; }"
    //        "QToolBar { background: blue; spacing: 10px;}"
    //        "QTableWidget QTableCornerButton::section { background: red; border: 2px outset red; }");
    //   QString style = R"(
    //               )";
    //m_pMenuBar->setStyleSheet(style);

    //QString style1 = R"(
    //               )";
    //menu->setStyleSheet(style1);
    //m_pMenuBar->setStyle();
    //m_pMenuBar->adjustSize();
    QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
    QMessageBoxEx::setCustomTextForButton(QMessageBox::No, "Нет");
    this->resetTabs();
    this->initTblView();
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

reportForm::~reportForm() {
    //delete model_;
    delete m_pMenuBar;
}

///-----------------------------------------------------------------------------
///
///         setMenuByUserRole
///          
///-----------------------------------------------------------------------------

void reportForm::setMenuByUserRole() {
    if (this->getUser().getRole() == 1) {
        QMenu * menu2 = m_pMenuBar->addMenu("&Справочники");
        // Справочники
        QAction *action = new QAction("&Список инспекций", this);
        connect(action, &QAction::triggered, this, &reportForm::OnInspection);
        menu2->addAction(action);
        action = new QAction("&Список МРО", this);
        connect(action, &QAction::triggered, this, &reportForm::OnMro);
        menu2->addAction(action);
        action = new QAction("&Статьи КоАП", this);
        connect(action, &QAction::triggered, this, &reportForm::OnArticle);
        menu2->addAction(action);
        action = new QAction("&Субъекты АП", this);
        connect(action, &QAction::triggered, this, &reportForm::OnSubject);
        menu2->addAction(action);
        action = new QAction("&Справочник колонок отчёта", this);
        connect(action, &QAction::triggered, this, &reportForm::OnRptColumn);
        menu2->addAction(action);
        action = new QAction("&Справочник строк отчёта", this);
        connect(action, &QAction::triggered, this, &reportForm::OnRptRow);
        menu2->addAction(action);
    }
}
///-----------------------------------------------------------------------------
///
///         setUser.
///          
///-----------------------------------------------------------------------------

void reportForm::setUser(const User& user) {
    user_ = user;
}

///-----------------------------------------------------------------------------
///
///         getUser.
///          
///-----------------------------------------------------------------------------

const User& reportForm::getUser() const {
    return user_;
}
///-----------------------------------------------------------------------------
///
///         getMenuBar.
///          
///-----------------------------------------------------------------------------

QMenuBar * reportForm::getMenuBar() {
    return m_pMenuBar;
}

///-----------------------------------------------------------------------------
///
///         Инициализировать указатели на QTableView
///          
///-----------------------------------------------------------------------------

void reportForm::initTblView() {

    tblview_[0] = this->widget.tableView;
    tblview_[1] = this->widget.tableView_2;
    tblview_[2] = this->widget.tableView_3;
    tblview_[3] = this->widget.tableView_4;

}
///-----------------------------------------------------------------------------
///
///         Меню.Формирование отчёта.Приложение 1.
///          
///-----------------------------------------------------------------------------

void reportForm::OnGenerateReport() {
    //QVBoxLayout *layout = new QVBoxLayout;
    //ayout->addWidget(widget->tableView);
    ///получен ответ от сервера в виде строки
    connect(this, SIGNAL(responseServer(const QString&)), this, SLOT(worker(const QString&)));
    QJsonObject param;
    emit runServerCmd(Functor<Mro>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    this->showControlsFrm();
    int mro = this->widget.tabWidget->currentIndex();
    if (mro == 0) {
        mro = 4;
    }
    report(mro);
    connect(this->widget.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
    //QMessageBox::information(0, "Menu", "Отчёт Приложение 1");
}
///-----------------------------------------------------------------------------
///
///         Меню.Формирование отчёта.Приложение 1.
///          
///-----------------------------------------------------------------------------

void reportForm::tabSelected() {

    array<QString, TAB_VIEW> listMro = reportForm::getListMroNameInReport();
    int selTabIndex = this->widget.tabWidget->currentIndex();
    if (!this->getTab(selTabIndex)) {
        selTabIndex == 0 ? report(4) : report(selTabIndex);
        model_[selTabIndex].setData(model_[selTabIndex].index(1, 0), listMro[selTabIndex], Qt::EditRole);
    } else {
        tblview_[selTabIndex]->setModel(&model_[selTabIndex]);
        setTableStyle(tblview_[selTabIndex]);
    }
}

///-----------------------------------------------------------------------------
///
///         Меню.Формирование отчёта.Приложение 2.
///          
///-----------------------------------------------------------------------------

void reportForm::OnGenerateReprt2() {
    for (int i = 0; i < 4; i++) {
        model_[i].clear();
    }
    this->resetTabs();
    this->hideControlsFrm();
}

///-----------------------------------------------------------------------------
///
///         Сбросить флаги заполнености таблиц.
///          
///-----------------------------------------------------------------------------

void reportForm::resetTabs() {

    tab_[0] = false;
    tab_[1] = false;
    tab_[2] = false;
    tab_[3] = false;
}

///-----------------------------------------------------------------------------
///
///         Получить  флаги заполнености таблиц.
///          
///-----------------------------------------------------------------------------

const array<bool, TAB_VIEW>& reportForm::getTabs() {
    return tab_;
}

///-----------------------------------------------------------------------------
///
///         Получить  флаг заполнености таблиц.
///          
///-----------------------------------------------------------------------------

const bool& reportForm::getTab(const int& i) {
    return tab_[i];
}


///-----------------------------------------------------------------------------
///
///         Установить флаг для заполнености таблиц.
///          
///-----------------------------------------------------------------------------

void reportForm::setTab(const int& i, const bool& fg) {
    tab_[i] = fg;
}



///-----------------------------------------------------------------------------
///
///         Меню.Выход из приложения.
///          
///-----------------------------------------------------------------------------

void reportForm::OnExit() {

    QMessageBoxEx::StandardButton reply;
    reply = QMessageBoxEx::question(this, "Завершение работы АРМ Инспектор",
            "Вы действительно хотите завершить работу ? ",
            QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        //this->close();
        //qApp->closeAllWindows();
        qApp->quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}


///-----------------------------------------------------------------------------
///
///         Меню.Список РЭГИ.
///          
///-----------------------------------------------------------------------------

void reportForm::OnInspection() {
    //QMessageBox::information(this, "АРМ Юриста", "OnInspection()");
    inspectionFrm* frm = new inspectionFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<InspectionView>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    emit runServerCmd(Functor<Mro>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Список инспекций");
    frm->setSizeTbl(853, 550);
    frm->exec();
}
///-----------------------------------------------------------------------------
///
///         Меню.Справочник колонок отчёта.
///          
///-----------------------------------------------------------------------------

void reportForm::OnRptColumn() {
    //QMessageBox::information(this, "АРМ Юриста", "OnRptColumn()");
    RptColumnFrm* frm = new RptColumnFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<RptColumnView>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    Nsi::num_ = NSI_ARTICLE;
    param.insert(NSI_NUM, Nsi::num_);
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    Nsi::num_ = NSI_SUBJECT;
    param[NSI_NUM] = Nsi::num_;
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Справочник колонок отчёта");
    frm->setSizeTbl(853, 550);
    frm->exec();


}

///-----------------------------------------------------------------------------
///
///         Меню.Справочник строк отчёта.
///          
///-----------------------------------------------------------------------------

void reportForm::OnRptRow() {
    //QMessageBox::information(this, "АРМ Юриста", "OnRptColumn()");
    RptRowFrm* frm = new RptRowFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<RptRow>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Справочник строк отчёта");
    frm->setSizeTbl(853, 550);
    frm->exec();


}

///-----------------------------------------------------------------------------
///
///         Меню.Список МРО.
///          
///-----------------------------------------------------------------------------

void reportForm::OnMro() {
    //QMessageBox::information(this, "АРМ Юриста", "OnMro()");
    mroFrm* frm = new mroFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    emit runServerCmd(Functor<MroView>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    emit runServerCmd(Functor<Inspection>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("МРО");
    frm->setSizeTbl(953, 200);
    frm->exec();
}

///-----------------------------------------------------------------------------
///
///         Меню.Справочник статей КоАП.
///          
///-----------------------------------------------------------------------------

void reportForm::OnArticle() {
    //QMessageBox::information(this, "АРМ Юриста", "Статьи КоАП");
    nsiFrm* frm = new nsiFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    Nsi::num_ = NSI_ARTICLE;
    param.insert(NSI_NUM, Nsi::num_);
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Статьи КоАП");
    frm->setSizeTbl(353, 570);
    frm->exec();
}


///-----------------------------------------------------------------------------
///
///         сигнально-слотовое соединение reportForm<---->nsiFrm
///          
///-----------------------------------------------------------------------------

void reportForm::createFrmConnector(const QDialog& frm) {
    ///выполнить команду на сервере
    connect(&frm, SIGNAL(runServerCmd(const QString&)), this, SIGNAL(runServerCmd(const QString&)));
    ///получен ответ от сервера в виде строки
    connect(this, SIGNAL(responseServer(const QString&)), &frm, SLOT(worker(const QString&)));
    // Сигнально - слотовое соединение ожидания ответа от сервера.
    connect(&frm, SIGNAL(waitReady()), this, SIGNAL(waitReady()));
    ///сигнал завершения процесса обработки
    connect(&frm, SIGNAL(ready()), this, SIGNAL(ready()));

}

///-----------------------------------------------------------------------------
///
///         Инициализация ссылки на контроллер клиента.
///         сигнально-слотовое соединение reportForm<---->m_pClientController
///          
///-----------------------------------------------------------------------------

void reportForm::initClient(ClientController *clientController) {
    m_pClientController = clientController;
    ///сигнал завершения процесса обработки
    connect(this, SIGNAL(ready()), m_pClientController, SLOT(formReady()));
    // Сигнально - слотовое соединение ожидания ответа от сервера.
    connect(this, SIGNAL(waitReady()), m_pClientController, SLOT(waitReady()));
    ///выполнить команду на сервере
    connect(this, SIGNAL(runServerCmd(const QString&)), m_pClientController,
            SLOT(runServerCmd(const QString&)));
    ///получен ответ от сервера в виде строки
    connect(m_pClientController, SIGNAL(responseServer(const QString&)),
            this, SIGNAL(responseServer(const QString&)));

};


///-----------------------------------------------------------------------------
///
///         Обработать команду (ответ) сервера.
///          
///-----------------------------------------------------------------------------

void reportForm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    ModelWrapper::Model model = wrapper.getEnumModel();
    switch (command) {
            ///-----------------------------------------------------------------------------
            ///
            ///                         GET_LIST_MODELS
            ///          
            ///-----------------------------------------------------------------------------
            //Сервер вернул результат команды "GET_LIST_MODELS"  

        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            //Сервер вернул результат команды "GET_LIST_MODELS"  
            //Процесс обработки возвращённого реультата.    

            switch (model) {
                case ModelWrapper::Model::Mro:
                {
                    ItemContainer<Mro> mroContainer;
                    JsonSerializer::parse(wrapper.getData(), mroContainer);
                    QList<Mro> listmro = mroContainer.getItemsList();
                    setlistMro(listmro);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::RptColumn:
                {
                    //QMessageBox::information(this, "RptColumn", "RptColumn");
                    ItemContainer<RptColumn> rptcolumnContainer;
                    JsonSerializer::parse(wrapper.getData(), rptcolumnContainer);
                    QList<RptColumn> listrptcolumn = rptcolumnContainer.getItemsList();
                    setlistCol(listrptcolumn);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::RptRow:
                {
                    //    QMessageBox::information(this, "RptRow", "RptRow");
                    ItemContainer<RptRow> rptrowContainer;
                    JsonSerializer::parse(wrapper.getData(), rptrowContainer);
                    QList<RptRow> listrptrow = rptrowContainer.getItemsList();
                    setlistRow(listrptrow);
                    emit ready();
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case ModelWrapper::Command::CALL_PROCEDURE:
        {
            switch (model) {
                case ModelWrapper::Model::Report:
                {
                    //QMessageBox::information(this, "CALL_PROCEDURE", "CALL_PROCEDURE");
                    //Сервер вернул результат команды "LOGIN"     
                    ItemContainer<ReportOut> rptoutContainer;
                    JsonSerializer::parse(wrapper.getData(), rptoutContainer);
                    QList<ReportOut> listresult = rptoutContainer.getItemsList();
                    setlistResult(listresult);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::ContextData:
                {
                    //QMessageBox::information(this, "CALL_PROCEDURE", "CALL_PROCEDURE");
                    //Сервер вернул результат команды "LOGIN"     
                    ItemContainer<ContextOut> contextoutContainer;
                    JsonSerializer::parse(wrapper.getData(), contextoutContainer);
                    QList<ContextOut> contextresult = contextoutContainer.getItemsList();
                    setContextResult(contextresult);
                    emit ready();
                }
                    break;
                default:
                    break;

            }

        }
            break;
        default:
            break;
    }
}


///-----------------------------------------------------------------------------
///
///         Справочник субъектов АП.
///          
///-----------------------------------------------------------------------------

void reportForm::OnSubject() {
    nsiFrm* frm = new nsiFrm();
    createFrmConnector(*frm);
    //frm->initClient(this->m_pClientController);
    QJsonObject param;
    Nsi::num_ = NSI_SUBJECT;
    param.insert(NSI_NUM, Nsi::num_);
    emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    frm->setWindowTitle("Субъекты АП");
    frm->setSizeTbl(353, 200);
    frm->exec();
}



///-----------------------------------------------------------------------------
///
///         Генерация формы отчёта из Excel.
///          
///-----------------------------------------------------------------------------

void reportForm::report(int mro) {
    //QMessageBox::critical(0, qApp->tr("Cannot open database"),
    //        qApp->tr("Unable to establish a database connection.\n"
    //        "This example needs SQLite support. Please read "
    //        "the Qt SQL driver documentation for information how "
    //        "to build it.\n\n"
    //        "Click Cancel to exit."), QMessageBox::Ok);
    QString filename;
    QTableView *tview;
    array<QString, TAB_VIEW> listExcel = reportForm::getListExcelFiles();
    filename = (mro == 4) ? listExcel[0] : listExcel[mro];
    tview = (mro == 4) ? tblview_[0] : tblview_[mro];

    QFile file(filename.toStdString().c_str());
    if (file.open(QIODevice::ReadOnly)) {
        //QMessageBox::information(this, "АРМ Юриста", "Отчет об АП");
        int lineindex = 0; // file line counter
        QTextStream in(&file); // read to text stream

        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n") 
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            //QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts); 
            QStringList lineToken = fileLine.split(";", QString::KeepEmptyParts);

            // load parsed data to model accordingly
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                mro == 4 ? model_[0].setItem(lineindex, j, item) : model_[mro].setItem(lineindex, j, item);

                item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                //item->setForeground();
                if (lineindex == 0 || lineindex == 7 || lineindex == 23 || lineindex == 26) {
                    //item->setForeground(QColor("orange"));
                    item->setFont(QFont("Times", 8, QFont::Bold, false));
                }
                if (lineindex == 1) {
                    if (j == 0) {
                        //                        item->setForeground(QColor("blue"));
                        item->setBackground(QColor("LightSkyBlue"));
                        item->setFont(QFont("Times", 8, QFont::Bold, false));
                    }
                    if (j == 8) {
                        item->setBackground(QColor("LightSkyBlue"));
                        //                        item->setForeground(QColor("red"));
                        item->setFont(QFont("Times", 8, QFont::Bold, false));
                    }
                }
                if (j == 0) {
                    if (lineindex > 1 && lineindex < 33) {
                        item->setBackground(QColor("LightGreen"));

                    }
                }
                if (j == 29) {
                    item->setBackground(QColor("LightGreen"));
                }
                if (j == 30) {
                    item->setBackground(QColor("LightPink"));
                }
                item->setToolTip("<a style='color:royalblue'> " + value + "</a>");
                item->setEditable(false);
                if (lineindex == 7 || lineindex == 23 || lineindex == 26) {
                    if (j == 0 || j == 1) {
                        item->setBackground(QColor("LightSkyBlue"));
                    }
                }
                if (lineindex == 33) {
                    item->setBackground(QColor("LightSkyBlue"));
                }

            }
            lineindex++;
        }
        file.close();
    }
    mro == 4 ? tview->setModel(&model_[0]) : tview->setModel(&model_[mro]);
    spanTbl(mro);
    setTableStyle(tview);
    disconnect(tview, SIGNAL(clicked(const QModelIndex &)), 0, 0);
    connect(tview, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
}
///-----------------------------------------------------------------------------
///
///         обработчик выбора Tab.
///          
///-----------------------------------------------------------------------------

void reportForm::onTableClicked(const QModelIndex &index) {
    if (index.isValid()&& index.column()>2&& index.column()<29 && index.row()<23&& index.row()>7) {
        QString cellText = index.data().toString();
        if (!cellText.isEmpty()) {
            ContextData model;
            int currentIndex = this->widget.tabWidget->currentIndex();
            int num_mro = (currentIndex == 0) ? 4 : currentIndex;
            model.setMro(num_mro);
            model.setMon(this->widget.dateEdit->date().month());
            model.setYear(this->widget.dateEdit->date().year());
            model.setCummulative(this->getCummulative());
            model.setNumcol(index.column() + 1);
            model.setNumrow(index.row() + 1);
            //QMessageBox::information(this, "АРМ Юриста", prd_);
            //QMessageBox::information(this, "АРМ Юриста", QString("%1___%2").arg(index.column()).arg(index.row()));
            emit runServerCmd(Functor<ContextData>::produce(ModelWrapper::Command::CALL_PROCEDURE, model));
            emit waitReady();
            ctxFrm frm;
            frm.displayTable(contextresult_);
            frm.exec();
        }
    }
}
///-----------------------------------------------------------------------------
///
///         Стиль таблицы.
///          
///-----------------------------------------------------------------------------

void reportForm::setTableStyle(QTableView* tview) {
    tview->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tview->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    tview->rowHeight(7);
    tview->columnWidth(7);
    tview->horizontalHeader()->setDefaultSectionSize(3);
    tview->verticalHeader()->setDefaultSectionSize(3);
    tview->verticalHeader()->setVisible(false);
    tview->horizontalHeader()->setVisible(false);
    //tview->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tview->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tview->setColumnWidth(1, 320);

    for (int i = 16; i < 29; i++) {
        tview->setColumnWidth(i, 50);
    }
    for (int i = 29; i < 31; i++) {
        tview->setColumnWidth(i, 120);
    }
    for (int i = 0; i < 35; i++) {
        if (i == 0) {
            tview->setColumnWidth(i, 70);
        }
        if (i > 7) {
            if (i != 10 && i != 21 && i != 22 && i != 23 && i != 24 && i != 25 && i != 26 && i != 33 && i != 34)
                tview->setRowHeight(i, 35);
        }
    }
}


///-----------------------------------------------------------------------------
///
///         Объединение ячеек таблицы.
///          
///-----------------------------------------------------------------------------

void reportForm::spanTbl(int mro) {
    QString filename;
    QTableView *tview;
    array<QString, TAB_VIEW> listExcel = reportForm::getListExcelFiles();
    filename = (mro == 4) ? listExcel[0] : listExcel[mro];
    tview = (mro == 4) ? tblview_[0] : tblview_[mro];

    QFile file(filename.toStdString().c_str());
    if (file.open(QIODevice::ReadOnly)) {
        //QMessageBox::information(this, "АРМ Юриста", "Отчет об АП");
        int lineindex = 0; // file line counter
        QTextStream in(&file); // read to text stream

        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n") 
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            //QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts); 
            QStringList lineToken = fileLine.split(";", QString::KeepEmptyParts);

            // load parsed data to model accordingly
            if (lineindex < 8 || lineindex == 23 || lineindex == 26 || lineindex == 33 || lineindex == 34 || lineindex == 35) {
                int spanCol = 1;
                int j = 0;
                for (; j < lineToken.size(); j++) {
                    QString value = lineToken.at(j);
                    if (value.isEmpty()) {
                        spanCol++;
                    } else {
                        ////qInfo() << QString::fromLocal8Bit(value.toStdString().c_str());
                        if (spanCol > 1) {
                            tview->setSpan(lineindex, j - spanCol, 1, spanCol);
                            //QString style = R"( )";
                            //tview->currentIndex()->child(lineindex, j - spanCol)->setStyleSheet(style);
                            spanCol = 1;
                        }
                    }
                    //QString style = R"()";
                }
                if (spanCol > 1) {
                    if (lineindex != 5) {
                        tview->setSpan(lineindex, j - spanCol, 1, spanCol);
                    }
                }
            }
            lineindex++;
        }

        file.close();
    }
}

///-----------------------------------------------------------------------------
///
///         Заполнение списка МРО
///          
///-----------------------------------------------------------------------------

void reportForm::setlistMro(const QList<Mro>& mro) {
    mro_ = mro;
    //this->widget.comboBox->clear();
    for (auto& t : mro_) {
        this->widget.tab->setWindowTitle(t.getName());
    }
}
///-----------------------------------------------------------------------------
///
///         Заполнение списка МРО
///          
///-----------------------------------------------------------------------------

void reportForm::setlistRow(const QList<RptRow>& listrow) {
    listrow_ = listrow;
}
///-----------------------------------------------------------------------------
///
///         Заполнение списка результата
///          
///-----------------------------------------------------------------------------

void reportForm::setlistResult(const QList<ReportOut>& result) {
    result_ = result;
}
///-----------------------------------------------------------------------------
///
///         Заполнение списка результата
///          
///-----------------------------------------------------------------------------

void reportForm::setContextResult(const QList<ContextOut>& result) {
    contextresult_ = result;
}
///-----------------------------------------------------------------------------
///
///         Заполнение списка МРО
///          
///-----------------------------------------------------------------------------

void reportForm::setlistCol(const QList<RptColumn>& listcol) {
    listcol_ = listcol;
}

///-----------------------------------------------------------------------------
///
///         Получить индикатор нарастающего итога.
///          
///-----------------------------------------------------------------------------

const qint64& reportForm::getCummulative() const {
    return cummulative_;
}

///-----------------------------------------------------------------------------
///
///         Установить индикатор нарастающего итога.
///          
///-----------------------------------------------------------------------------

void reportForm::setCummulative() {
    int mon = this->widget.dateEdit->date().month();
    int kv = mon / 3;
    kv = (mon % 3 > 0) ? ++kv : kv;
    ///Получить значение RadioBox
    QList<QRadioButton *> buttons;
    buttons = this->widget.groupBox->findChildren<QRadioButton *>();
    int period = 0;
    for (int i = 1; i <= buttons.size(); ++i) {
        if (buttons[i - 1]->isChecked()) {
            period = i;
            break;
        }
    }
    //Определение индикатора нарастающего итога .
    switch (period) {
        case 1://Данные за месяц
        {
            cummulative_ = 0;
        }
            break;
        case 2://Данные за квартал
        {

            cummulative_ = kv;
        }
            break;
        case 3://Данные с начала года
        {
            cummulative_ = 11;
        }
            break;
    }
}

///-----------------------------------------------------------------------------
///
///         Получить строку периода отчёта.
///          
///-----------------------------------------------------------------------------

const QString& reportForm::getPeriod() const {
    return prd_;
}
///-----------------------------------------------------------------------------
///
///         Установить строку периода отчёта.
///          
///-----------------------------------------------------------------------------

void reportForm::setPeriod() {
    int mon = this->widget.dateEdit->date().month();
    int year = this->widget.dateEdit->date().year();
    int kv = mon / 3;
    kv = (mon % 3 > 0) ? ++kv : kv;
    ///Получить значение RadioBox
    QList<QRadioButton *> buttons;
    buttons = this->widget.groupBox->findChildren<QRadioButton *>();
    int period = 0;
    for (int i = 1; i <= buttons.size(); ++i) {
        if (buttons[i - 1]->isChecked()) {
            period = i;
            break;
        }
    }
    //Определение периода отчёта.
    prd_ = "";
    switch (period) {
        case 1://Данные за месяц
        {
            prd_ += this->widget.dateEdit->date().longMonthName(mon); //название месяца
            prd_ += " ";
            prd_ += QString::number(year); //год
            prd_ += " года";
        }
            break;
        case 2://Данные за квартал
        {

            prd_ += QString::number(kv); //квартал
            prd_ += " квартал ";
            prd_ += QString::number(year);
            prd_ += " года";
        }
            break;
        case 3://Данные с начала года
        {
            prd_ += QString::number(year);
            prd_ += " год(С начала года).";
        }
            break;
    }
}

///-----------------------------------------------------------------------------
///
///         Нажата кнопка выгрузки отчёта в Excel.
///          
///-----------------------------------------------------------------------------

/*void reportForm::on_pushButton_Excel_clicked() {
    this->setPeriod();
    if (this->getPeriod().isEmpty()) {
        QMessageBox::information(this, "АРМ Юриста", "Не задан период отчёта");
        showButtons();
        return;
    }

    int selTabIndex = this->widget.tabWidget->currentIndex();
    array<QString, TAB_VIEW>listName = reportForm::getListMroName();
    array<QString, TAB_VIEW> listMRO = getListMroNameInReport();

    //QMessageBox::information(this, "АРМ Юриста", "Выгрузка в Excel");
    // получаем указатель на Excel
    QAxObject *mExcel = new QAxObject("Excel.Application", this);
    mExcel-> setProperty("Visible", true);
    // на книги
    QAxObject *workbooks = mExcel->querySubObject("Workbooks");
    QDir dir(".");
    //QMessageBox::information(this, "АРМ Юриста", dir.absolutePath());
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)",
            QString(dir.absolutePath() + "/Tmp/" + listName[selTabIndex] + ".xlsx"));

    if (workbook == NULL) {
        QMessageBox::information(this, "АРМ Юриста", "Open Excel error");
        return;
    }
    if (selTabIndex > 0) {//по МРО
        // на листы
        QAxObject *mSheets = workbook->querySubObject("Sheets");
        if (mSheets == NULL) {
            QMessageBox::information(this, "АРМ Юриста", "Sheets Excel error");
            return;
        }
        // указываем, какой лист выбрать
        QAxObject *StatSheet = mSheets->querySubObject("Item(const QVariant&)", QVariant(listName[selTabIndex]));
        if (StatSheet == NULL) {
            QMessageBox::information(this, "АРМ Юриста", "StatSheet Excel error");
            return;
        }
        // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
        QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", 3, 1);
        cell->setProperty("Value", QVariant(listMRO[selTabIndex] + " за " + this->getPeriod()));
        delete cell;
        for (int row = 0; row < this->model_[selTabIndex].rowCount(); row++) {
            if (row == 1) {
                // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
                QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", 3, 1);
                cell->setProperty("Value", QVariant(model_[selTabIndex].data(model_[selTabIndex].index(row, 0))).toString() + " за " + this->getPeriod());
                delete cell;
            }
            if (row > 7 && row < 33 && row != 23 && row != 26) {
                for (int col = 0; col < this->model_[selTabIndex].columnCount(); col++) {
                    if (col > 3) {
                        // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
                        QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", row + 1, col + 1);
                        // вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
                        if (QVariant(model_[selTabIndex].data(model_[selTabIndex].index(row, col))).toDouble() > 0) {
                            if (row == 24 || row == 25) {
                                cell->setProperty("Value", QVariant(model_[selTabIndex].data(model_[selTabIndex].index(row, col))).toDouble());
                            } else {
                                cell->setProperty("Value", QVariant(model_[selTabIndex].data(model_[selTabIndex].index(row, col))).toInt());
                            }
                        } else {
                            cell->clear();
                        }
                        delete cell;
                    }
                }
            }
        }
    } else {//по филиалу
        for (int mro = 1; mro < 4; mro++) {
            // на листы
            QAxObject *mSheets = workbook->querySubObject("Sheets");
            if (mSheets == NULL) {
                QMessageBox::information(this, "АРМ Юриста", "Sheets Excel error");
                return;
            }
            // указываем, какой лист выбрать
            QAxObject *StatSheet = mSheets->querySubObject("Item(const QVariant&)", QVariant(listName[mro]));
            if (StatSheet == NULL) {
                QMessageBox::information(this, "АРМ Юриста", "StatSheet Excel error");
                return;
            }
            // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
            QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", 3, 1);
            cell->setProperty("Value", QVariant(listMRO[mro] + " за " + this->getPeriod()));
            delete cell;
            for (int row = 0; row < this->model_[mro].rowCount(); row++) {
                if (row > 7 && row < 33 && row != 23 && row != 26) {
                    for (int col = 0; col < this->model_[mro].columnCount(); col++) {
                        if (col > 3) {
                            // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
                            QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", row + 1, col + 1);
                            // вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
                            if (QVariant(model_[mro].data(model_[mro].index(row, col))).toDouble() > 0) {
                                if (row == 24 || row == 25) {
                                    cell->setProperty("Value", QVariant(model_[mro].data(model_[mro].index(row, col))).toDouble());
                                } else {
                                    cell->setProperty("Value", QVariant(model_[mro].data(model_[mro].index(row, col))).toInt());
                                }
                            } else {
                                cell->clear();
                            }
                            delete cell;
                        }
                    }
                }
            }
        }
        // на листы
        QAxObject *mSheets = workbook->querySubObject("Sheets");
        if (mSheets == NULL) {
            QMessageBox::information(this, "АРМ Юриста", "Sheets Excel error");
            return;
        }
        // указываем, какой лист выбрать
        QAxObject *StatSheet = mSheets->querySubObject("Item(const QVariant&)", QVariant(listName[0]));
        if (StatSheet == NULL) {
            QMessageBox::information(this, "АРМ Юриста", "StatSheet Excel error");
            return;
        }
        // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
        QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", 3, 1);
        cell->setProperty("Value", QVariant(listMRO[0] + " за " + this->getPeriod()));
        delete cell;
    }

}*/





///-----------------------------------------------------------------------------
///
///         Нажата кнопка формирования отчёта.
///          
///-----------------------------------------------------------------------------

/*void reportForm::on_pushButton_Excel_clicked() {

    QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    xlsx.saveAs("TestExcel.xlsx"); // save the document as 'Test.xlsx'
    // [2] Reading excel file(*.xlsx)
    Document xlsxR("TestExcel.xlsx");
    if (xlsxR.load()) // load excel file
    {
        int row = 1;
        int col = 1;
        Cell* cell = xlsxR.cellAt(row, col); // get cell pointer.
        if (cell != NULL) {
            QVariant var = cell->readValue(); // read cell value (number(double), QDateTime, QString ...)
            qDebug() << var; // display value. it is 'Hello Qt!'.
        }
    }
    tview->clearFocus();
    QAxWidget* ExcelDocument = new QAxWidget("Excel.Application", this->widget.tableView);
    ExcelDocument-> setGeometry(QRect(1, 1, 1900, 1200));
    ExcelDocument->setControl("d:/MyProjects_2021/ARMInspector/ARMInspectorGUI/ExcelDocs/3.xlsx");
    ExcelDocument-> show();

}

void Window::importExcelToDatabase()
{
         QString strFilePathName = QFileDialog :: getOpenFileName (this, QStringLiteral ( "Select the Excel file"), "", tr ( "Exel file (* xls * .xlsx)").);
        if(strFilePathName.isNull())
        {
                return ;
        }
         QAxObject * excel = new QAxObject (this); // connect Excel Controls
        if(excel->setControl("Excel.Application"))
        {
        excel->setControl("Excel.Application")
        }
        else
        {
                 excel-> setControl ( "ket.Application"); // connect Excel Controls
        }
         excel-> setProperty ( "Visible", false); // do not display the form
         QAxObject * workbooks = excel-> querySubObject ( "WorkBooks"); // get a set of workbooks
         workbooks-> dynamicCall ( "Open (const QString &)", strFilePathName); // Open to open an existing workbook
         QAxObject * workbook = excel-> querySubObject ( "ActiveWorkBook"); // Get the current workbook 
         QAxObject * sheets = workbook-> querySubObject ( "Sheets"); // Get the sheet set, Sheets may be substituted therefore WorkSheets
         QAxObject * sheet = workbook-> querySubObject ( "WorkSheets (int)", 1); // Get worksheets collection sheet 1, i.e. sheet1
         QAxObject * range = sheet-> querySubObject ( "UsedRange"); // Get the scope of use of the sheet objects
        QVariant var = range->dynamicCall("Value");
        delete range;
         QVariantList varRows = var.toList (); // get all the data in the table
        if(varRows.isEmpty())
        {
                return;
        }
        const int rowCount = varRows.size();
        QStringList m_userid,m_card_id,m_action;
        for(int i = 1; i < rowCount; ++i)   //
        {
                QVariantList rowData = varRows[i].toList();
                m_userid<<rowData[0].toString();
                m_card_id<<rowData[1].toString();
                m_action<<rowData[2].toString();
        }
}
 */
///-----------------------------------------------------------------------------
///
///         Нажата кнопка формирования отчёта.
///          
///-----------------------------------------------------------------------------

void reportForm::on_pushButton_Report_clicked() {

    QJsonObject param;
    emit runServerCmd(Functor<RptRow>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();
    emit runServerCmd(Functor<RptColumn>::producePrm(ModelWrapper::GET_LIST_MODELS, param));
    emit waitReady();


    this->showControlsFrm();
    hideButtons();
    int currentIndex = this->widget.tabWidget->currentIndex();
    array<QString, TAB_VIEW>listName = reportForm::getListMroName();
    array<QString, TAB_VIEW> listMRO = getListMroNameInReport();
    model_[currentIndex].clear();
    int num_mro = (currentIndex == 0) ? 4 : currentIndex;
    this->setTab(currentIndex, false);
    this->report(num_mro);
    //    model_->setData(model_->index(1, 8), "май 2021 года", Qt::EditRole);
    Report model;
    model.setMro(num_mro);
    model.setMon(this->widget.dateEdit->date().month());
    model.setYear(this->widget.dateEdit->date().year());
    this->setPeriod();
    if (this->getPeriod().isEmpty()) {
        QMessageBox::information(this, "АРМ Юриста", "Не задан период отчёта");
        showButtons();
        return;
    }
    this->setCummulative();
    model.setCummulative(this->getCummulative());
    //QMessageBox::information(this, "АРМ Юриста", prd_);
    if (currentIndex > 0) {
        this->setTab(currentIndex, true);
        model_[currentIndex].setData(model_[currentIndex].index(1, 0), listMRO[currentIndex], Qt::EditRole);
        model_[currentIndex].setData(model_[currentIndex].index(1, 8), this->getPeriod(), Qt::EditRole);

        myProgressBar* frmProgress = new myProgressBar(this);
        frmProgress->setWindowTitle("Формирование отчёта " + listName[currentIndex] + " МРО  за  " + this->getPeriod());
        frmProgress->getUI()->progressBar->setStyleSheet("QProgressBar {"
                "border: 2px solid grey;"
                "border-radius: 5px;"
                "text-align: center;"
                "}"
                "QProgressBar::chunk {"
                "background-color: #05B8CC;"
                "width: 20px;}");

        frmProgress->setWindowFlags(frmProgress->windowFlags() & ~Qt::WindowCloseButtonHint);
        frmProgress->getUI()->progressBar->setMinimum(0);
        frmProgress->getUI()->progressBar->setMaximum(listrow_.size() * listcol_.size());
        frmProgress->setAttribute(Qt::WA_DeleteOnClose);
        frmProgress->show();
        for (int i = 0; i < listrow_.size(); i++) {
            RptRow rptrow = listrow_.at(i);
            model.setNumrow(rptrow.getRow());
            emit runServerCmd(Functor<Report>::produce(ModelWrapper::Command::CALL_PROCEDURE, model));
            emit waitReady();
            int col = 0;
            int mon_total = 0;
            double sum_total = 0;
            bool sum = false;
            if (rptrow.getRow() == 25 || rptrow.getRow() == 26) {//строки сумм штрафов
                sum = true;
            } else {
                sum = false;
            }
            for (int j = 0; j < result_.size(); j++) {
                frmProgress->getUI()->progressBar->setValue(frmProgress->getUI()->progressBar->value() + 1);
                col = j + 2;
                ReportOut rptout = result_.at(j);
                if (rptout.getCount() > 0) {
                    if (rptout.getCol() < 29) {
                        if (sum) {
                            sum_total += rptout.getCount();
                        } else {
                            mon_total += rptout.getCount();
                        }
                        model_[currentIndex].setData(model_[currentIndex].index(rptrow.getRow() - 1, rptout.getCol() - 1), rptout.getCount(), Qt::EditRole);
                    } else if (rptout.getCol() == 30) {
                        model_[currentIndex].setData(model_[currentIndex].index(rptrow.getRow() - 1, rptout.getCol()), rptout.getCount(), Qt::EditRole);
                    }

                }
            }
            if (mon_total > 0 || sum_total > 0) {
                if (sum) {
                    model_[currentIndex].setData(model_[currentIndex].index(rptrow.getRow() - 1, col), QString::number(sum_total, 'f', 2), Qt::EditRole);

                } else {

                    model_[currentIndex].setData(model_[currentIndex].index(rptrow.getRow() - 1, col), QString::number(mon_total), Qt::EditRole);
                }
            }
        }
        frmProgress->close();
        connect(frmProgress->getUI()->progressBar, SIGNAL(destroyed()), this, SLOT(showButtons()));

    } else {
        this->resetTabs();
        for (int mro = 0; mro < 4; mro++) {
            num_mro = (mro == 0) ? 4 : mro;
            model.setMro(num_mro);
            this->widget.tabWidget->setCurrentIndex(mro);
            this->setTab(mro, true);
            model_[mro].setData(model_[mro].index(1, 0), listMRO[mro], Qt::EditRole);
            model_[mro].setData(model_[mro].index(1, 8), this->getPeriod(), Qt::EditRole);

            myProgressBar* frmProgress = new myProgressBar(this);
            if (mro == 0) {
                frmProgress->setWindowTitle("Формирование отчёта " + listName[mro] + " за  " + this->getPeriod());
            } else {
                frmProgress->setWindowTitle("Формирование отчёта " + listName[mro] + " МРО за  " + this->getPeriod());
            }

            frmProgress->getUI()->progressBar->setStyleSheet("QProgressBar {"
                    "border: 2px solid grey;"
                    "border-radius: 5px;"
                    "text-align: center;"
                    "}"
                    "QProgressBar::chunk {"
                    "background-color: #05B8CC;"
                    "width: 20px;}");
            frmProgress->setWindowFlags(frmProgress->windowFlags() & ~Qt::WindowCloseButtonHint);
            frmProgress->getUI()->progressBar->setMinimum(0);
            frmProgress->getUI()->progressBar->setMaximum(listrow_.size() * listcol_.size());

            frmProgress->getUI()->progressBar->setWindowTitle(listMRO[mro]);
            frmProgress->setAttribute(Qt::WA_DeleteOnClose);
            frmProgress->show();
            for (int i = 0; i < listrow_.size(); i++) {
                RptRow rptrow = listrow_.at(i);
                model.setNumrow(rptrow.getRow());
                emit runServerCmd(Functor<Report>::produce(ModelWrapper::Command::CALL_PROCEDURE, model));
                emit waitReady();
                int col = 0;
                int mon_total = 0;
                double sum_total = 0;
                bool sum = false;
                if (rptrow.getRow() == 25 || rptrow.getRow() == 26) {//строки сумм штрафов
                    sum = true;
                } else {
                    sum = false;
                }
                for (int j = 0; j < result_.size(); j++) {
                    frmProgress->getUI()->progressBar->setValue(frmProgress->getUI()->progressBar->value() + 1);
                    col = j + 2;
                    ReportOut rptout = result_.at(j);
                    if (rptout.getCount() > 0) {
                        if (rptout.getCol() < 29) {
                            if (sum) {
                                sum_total += rptout.getCount();
                            } else {
                                mon_total += rptout.getCount();
                            }
                            model_[mro].setData(model_[mro].index(rptrow.getRow() - 1, rptout.getCol() - 1), rptout.getCount(), Qt::EditRole);
                        } else if (rptout.getCol() == 30) {
                            model_[mro].setData(model_[mro].index(rptrow.getRow() - 1, rptout.getCol()), rptout.getCount(), Qt::EditRole);
                        }

                    }
                }
                if (mon_total > 0 || sum_total > 0) {
                    if (sum) {
                        model_[mro].setData(model_[mro].index(rptrow.getRow() - 1, col), QString::number(sum_total, 'f', 2), Qt::EditRole);

                    } else {

                        model_[mro].setData(model_[mro].index(rptrow.getRow() - 1, col), QString::number(mon_total), Qt::EditRole);
                    }
                }
            }
            frmProgress->close();
            delete frmProgress;
        }
        showButtons();
        this->widget.tabWidget->setCurrentIndex(0);
    }
}



///-----------------------------------------------------------------------------
///
///         Показать кнопки
///          
///-----------------------------------------------------------------------------

void reportForm::showButtons() {
    //QMessageBox::information(this, "АРМ Юриста", "showButton()");

    this->widget.pushButton_Excel->show();
    this->widget.pushButton_Report->show();

}

///-----------------------------------------------------------------------------
///
///         Скрыть  кнопки
///          
///-----------------------------------------------------------------------------

void reportForm::hideButtons() {
    //QMessageBox::information(this, "АРМ Юриста", "showButton()");

    this->widget.pushButton_Excel->hide();
    this->widget.pushButton_Report->hide();

}
///-----------------------------------------------------------------------------
///
///         Спрятать элементы формы отчёта.
///          
///-----------------------------------------------------------------------------

void reportForm::hideControlsFrm() {

    //his->widget.comboBox->setHidden(true);

    this->widget.tabWidget->setHidden(true);
    this->widget.dateEdit->setHidden(true);
    this->widget.groupBox->setHidden(true);
    this->widget.tableView->setHidden(true);
    this->widget.pushButton_Excel->setHidden(true);
    this->widget.pushButton_Report->setHidden(true);
    this->widget.label_Data->setHidden(true);
    //this->widget.label_Mro->setHidden(true);
    this->widget.label_Period->setHidden(true);
}

///-----------------------------------------------------------------------------
///
///         Показать элементы формы отчёта.
///          
///-----------------------------------------------------------------------------

void reportForm::showControlsFrm() {
    //this->widget.comboBox->setVisible(true);
    this->widget.tabWidget->setVisible(true);
    this->widget.dateEdit->setVisible(true);
    this->widget.groupBox->setVisible(true);
    this->widget.tableView->setVisible(true);
    this->widget.pushButton_Excel->setVisible(true);
    this->widget.pushButton_Report->setVisible(true);
    this->widget.label_Data->setVisible(true);
    //this->widget.label_Mro->setVisible(true);
    this->widget.label_Period->setVisible(true);
    int inspection = this->getUser().getInspection();
    if (inspection == 1) {
        this->widget.tabWidget->setCurrentIndex(1);
        this->widget.tabWidget->setTabEnabled(0, false);
        this->widget.tabWidget->setTabEnabled(2, false);
        this->widget.tabWidget->setTabEnabled(3, false);
    } else if (inspection == 7) {
        this->widget.tabWidget->setCurrentIndex(2);
        this->widget.tabWidget->setTabEnabled(0, false);
        this->widget.tabWidget->setTabEnabled(1, false);
        this->widget.tabWidget->setTabEnabled(3, false);
    } else if (inspection == 12) {
        this->widget.tabWidget->setCurrentIndex(3);
        this->widget.tabWidget->setTabEnabled(0, false);
        this->widget.tabWidget->setTabEnabled(1, false);
        this->widget.tabWidget->setTabEnabled(2, false);
    }
}
//  QFile styleF;
//    styleF.setFileName(":/qss/style.qss");
//    styleF.open(QFile::ReadOnly);
//    QString qssStr = styleF.readAll();
//    qApp->setStyleSheet(qssStr);
//https://www.programmersought.com/article/2906246923/

//void reportForm::closeEvent(QCloseEvent *event) {
//    event->accept();
//    QMainWindow::closeEvent(event);
//(new DialogDestroyer())->DelayedDestruction(this);
//}