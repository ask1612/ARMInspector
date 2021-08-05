/********************************************************************************
** Form generated from reading UI file 'ctxFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTXFRM_H
#define UI_CTXFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ctxFrm
{
public:
    QTableWidget *tableWidget;

    void setupUi(QDialog *ctxFrm)
    {
        if (ctxFrm->objectName().isEmpty())
            ctxFrm->setObjectName(QString::fromUtf8("ctxFrm"));
        ctxFrm->resize(501, 300);
        ctxFrm->setMaximumSize(QSize(16777202, 16777215));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        ctxFrm->setFont(font);
        ctxFrm->setToolTipDuration(-9);
        ctxFrm->setStyleSheet(QString::fromUtf8("QTableView#tableWidget QHeaderView\n"
"{\n"
"    /* draw the hole hor top & bottom line for the header */\n"
"    height: 24px;\n"
"\n"
"    border-top: 1px solid #161618;\n"
"    border-bottom: 1px solid #161618;\n"
"}\n"
"\n"
"QTableView#tableWidget QHeaderView::section:horizontal:first\n"
"{\n"
"    border-left-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f4f4f6, stop:1 #ceced6);\n"
"}\n"
"\n"
"QTableView#tableWidget QHeaderView::section:horizontal:last\n"
"{\n"
"    border-right-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f4f4f6, stop:1 #ceced6);\n"
"}\n"
"\n"
"QTableView#tableWidget QHeaderView::section:horizontal\n"
"{\n"
"    /* for each section draw ONLY left & right lines */\n"
"    height: 24px;\n"
"\n"
"    border-style: none;\n"
"\n"
"    border-left: 1px solid #ecedef;\n"
"    border-right: 1px solid #b1b1b5;\n"
"\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f4f4f6, stop:1 #ceced6);\n"
"\n"
" }"));
        tableWidget = new QTableWidget(ctxFrm);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(40, 20, 411, 241));

        retranslateUi(ctxFrm);

        QMetaObject::connectSlotsByName(ctxFrm);
    } // setupUi

    void retranslateUi(QDialog *ctxFrm)
    {
        ctxFrm->setWindowTitle(QCoreApplication::translate("ctxFrm", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\264\320\265\320\273 \320\220\320\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ctxFrm: public Ui_ctxFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTXFRM_H
