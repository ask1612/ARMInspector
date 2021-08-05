/********************************************************************************
** Form generated from reading UI file 'reportFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTFRM_H
#define UI_REPORTFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_reportFrm
{
public:
    QTableView *tableView;

    void setupUi(QDialog *reportFrm)
    {
        if (reportFrm->objectName().isEmpty())
            reportFrm->setObjectName(QString::fromUtf8("reportFrm"));
        reportFrm->resize(1227, 900);
        reportFrm->setCursor(QCursor(Qt::UpArrowCursor));
        reportFrm->setContextMenuPolicy(Qt::PreventContextMenu);
        tableView = new QTableView(reportFrm);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(35, 30, 1151, 841));

        retranslateUi(reportFrm);

        QMetaObject::connectSlotsByName(reportFrm);
    } // setupUi

    void retranslateUi(QDialog *reportFrm)
    {
        reportFrm->setWindowTitle(QCoreApplication::translate("reportFrm", "\320\236\321\202\321\207\320\265\321\202 \320\277\320\276 \320\260\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\270\320\262\320\275\320\276\320\274\321\203 \320\277\321\200\320\276\320\270\320\267\320\262\320\276\320\264\321\201\321\202\320\262\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reportFrm: public Ui_reportFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTFRM_H
