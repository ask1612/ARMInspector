/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ctxFrm.cpp
 * Author: kazun_as
 *
 * Created on 30 июля 2021 г., 09:50
 */

#include "ctxFrm.h"
#include "QMessageBoxEx.h"
#include "docsAP.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

ctxFrm::ctxFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::ctxFrm) {
    QStringList headers = QStringList({"Рег. номер", "ФИО нарушителя"});
    widget_->setupUi(this);
    widget_->tableWidget->setColumnCount(2);
    widget_->tableWidget->setShowGrid(true);
    widget_->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    widget_->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    widget_->tableWidget->setHorizontalHeaderLabels(headers);
    widget_->tableWidget->horizontalHeader()->setStretchLastSection(true);
    QHeaderView *vh = new QHeaderView(Qt::Vertical);
    vh->hide();
    widget_->tableWidget->setVerticalHeader(vh);

}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

ctxFrm::~ctxFrm() {
    delete widget_;
}

///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::ctxFrm* ctxFrm::getUI() {
    return widget_;
}

///-----------------------------------------------------------------------------
///
///         Вывести данные на экран.
///          
///-----------------------------------------------------------------------------

void ctxFrm::displayTable(const QList<ContextOut>& list) {
    for (int i = 0; i < list.size(); i++) {
        ContextOut model = list.at(i);
        widget_->tableWidget->insertRow(i);
        widget_->tableWidget->setItem(i, 0, new QTableWidgetItem(model.getRegnum()));
        widget_->tableWidget->setItem(i, 1, new QTableWidgetItem(model.getFio()));
        
        //QModelIndex modelIndex =widget_->tableWidget->currentIndex();
        disconnect(widget_->tableWidget, SIGNAL(clicked(const QModelIndex &)), 0, 0);
        connect(widget_->tableWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    }

}

///-----------------------------------------------------------------------------
///
///         обработчик выбора Tab.
///          
///-----------------------------------------------------------------------------

void ctxFrm::onTableClicked(const QModelIndex &index) {
    QString cellText = index.siblingAtColumn(0).data().toString();
    //QMessageBox::information(this, "АРМ Юриста", cellText);
    docsAP frm;
    frm.personView();
    frm.exec();
 }