/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   docsAP.cpp
 * Author: kazun_as
 *
 * Created on 30 июля 2021 г., 15:24
 */

#include "docsAP.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

docsAP::docsAP(QWidget *parent) :
QDialog(parent), widget_(new Ui::docsAP) {
    widget_->setupUi(this);
}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

docsAP::~docsAP() {
    delete widget_;

}
///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::docsAP* docsAP::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         Вывести данные об АП.
///          
///-----------------------------------------------------------------------------

void docsAP::personView() {
    //tradeWidget = new QWidget;  // this is a hidden top-level QWidget
    //tradeWidget->setWindowTitle("Trade View");

    //tradeWidget->setGeometry(150,18,1800,800);
    QHBoxLayout* layout = new QHBoxLayout();
    QTabWidget* pTabWidget = new QTabWidget(this);
    for (int i = 0; i < 2; i++) {
        QStringList headers = QStringList({"Рег. номер", "ФИО нарушителя"});
        QTableWidget* pTableWidget = new QTableWidget(this);
        pTabWidget->addTab(pTableWidget, "tab_"+QString::number(i));
        pTableWidget->setRowCount(100);
        pTableWidget->setColumnCount(2);
        //m_TableHeader<<"Client Id"<<"Symbol"<<"Quantity"<<"Strategy Id"<<"Expiry" << "Side";
        pTableWidget->setHorizontalHeaderLabels(headers);
        //pTableWidget->setVerticalHeader();
        pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        //pTableWidget->horizontalHeader()->setStretchLastSection(true);
        pTableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
        pTableWidget->setShowGrid(true);
        pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        QHeaderView* header = pTableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Stretch);
    }
    layout->addWidget(pTabWidget);
    this->setLayout(layout);

}