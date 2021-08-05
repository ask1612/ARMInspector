/********************************************************************************
** Form generated from reading UI file 'RptRowFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RPTROWFRM_H
#define UI_RPTROWFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_RptRowFrm
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_Edit;
    QPushButton *pushButton_Remove;

    void setupUi(QDialog *RptRowFrm)
    {
        if (RptRowFrm->objectName().isEmpty())
            RptRowFrm->setObjectName(QString::fromUtf8("RptRowFrm"));
        RptRowFrm->resize(502, 375);
        RptRowFrm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 100px;\n"
"max-width: 100px;\n"
"min-height: 13px;\n"
"max-height: 13px;\n"
"}\n"
"QHeaderView {\n"
"    background-color: #fff;\n"
"    font-size:11px;\n"
"}\n"
"QHeaderView::section:horizontal {\n"
"    color: #fff;\n"
"    border-style: solid;\n"
"    background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                        stop: 0 #4287ff, stop: 1 #356ccc);\n"
" }\n"
"QTableView {\n"
"    border: 1px solid #3873d9;\n"
"    border-top-color: #4287ff;\n"
"    border-radius: 4px;\n"
"    background-color: #fff;\n"
"    background-image: url(:/img/other/background.png);\n"
"    gridline-color: #777;\n"
"    selec"
                        "tion-background-color: rgb(235,110,36);\n"
"    color:#333;\n"
"    font-size:11px;\n"
" }\n"
"\n"
"QScrollBar:vertical {\n"
"     background: #e4e4e4;\n"
"     border-top-right-radius: 4px;\n"
"     border-bottom-right-radius: 4px;\n"
"     width: 12px;\n"
"     margin: 0px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"    background-color: qlineargradient( x1: 0, y1: 0, x2: 1, y2: 0,\n"
"                                    stop: 0 #4287ff, stop: 1 #356ccc);\n"
"     border-radius: 4px;\n"
"     min-height: 20px;\n"
"     margin: 0px 2px 0px 2px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"     background: none;\n"
"     height: 0px;\n"
"     subcontrol-position: right;\n"
"     subcontrol-origin: margin;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"     background: none;\n"
"     height: 0px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
"QMessageBox QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d"
                        ", stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 50px;\n"
"max-width: 50px;\n"
"min-height: 13px;\n"
"max-height: 13px;\n"
"}\n"
""));
        gridLayout = new QGridLayout(RptRowFrm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(RptRowFrm);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 3);

        pushButton_Add = new QPushButton(RptRowFrm);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));

        gridLayout->addWidget(pushButton_Add, 1, 0, 1, 1);

        pushButton_Edit = new QPushButton(RptRowFrm);
        pushButton_Edit->setObjectName(QString::fromUtf8("pushButton_Edit"));

        gridLayout->addWidget(pushButton_Edit, 1, 1, 1, 1);

        pushButton_Remove = new QPushButton(RptRowFrm);
        pushButton_Remove->setObjectName(QString::fromUtf8("pushButton_Remove"));

        gridLayout->addWidget(pushButton_Remove, 1, 2, 1, 1);


        retranslateUi(RptRowFrm);

        QMetaObject::connectSlotsByName(RptRowFrm);
    } // setupUi

    void retranslateUi(QDialog *RptRowFrm)
    {
        RptRowFrm->setWindowTitle(QCoreApplication::translate("RptRowFrm", "RptColumnFrm", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("RptRowFrm", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 ", nullptr));
        pushButton_Edit->setText(QCoreApplication::translate("RptRowFrm", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 ", nullptr));
        pushButton_Remove->setText(QCoreApplication::translate("RptRowFrm", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RptRowFrm: public Ui_RptRowFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RPTROWFRM_H
