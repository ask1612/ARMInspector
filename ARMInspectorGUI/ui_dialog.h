/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog
{
public:
    QTableView *tableView;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_addUser;
    QPushButton *pushButton_editUser;
    QPushButton *pushButton_deleteUser;
    QPushButton *pushButton_changePassword;

    void setupUi(QDialog *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QString::fromUtf8("dialog"));
        dialog->resize(718, 701);
        dialog->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"min-width: 150px;\n"
"max-width: 150px;\n"
"min-height: 13px;\n"
"max-height: 13px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #4169E1;     \n"
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
"    background-image: url("
                        ":/img/other/background.png);\n"
"    gridline-color: #777;\n"
"    selection-background-color: rgb(235,110,36);\n"
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
"bac"
                        "kground-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
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
        tableView = new QTableView(dialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 10, 691, 641));
        layoutWidget = new QWidget(dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 670, 668, 23));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_addUser = new QPushButton(layoutWidget);
        pushButton_addUser->setObjectName(QString::fromUtf8("pushButton_addUser"));

        gridLayout->addWidget(pushButton_addUser, 0, 0, 1, 1);

        pushButton_editUser = new QPushButton(layoutWidget);
        pushButton_editUser->setObjectName(QString::fromUtf8("pushButton_editUser"));

        gridLayout->addWidget(pushButton_editUser, 0, 1, 1, 1);

        pushButton_deleteUser = new QPushButton(layoutWidget);
        pushButton_deleteUser->setObjectName(QString::fromUtf8("pushButton_deleteUser"));

        gridLayout->addWidget(pushButton_deleteUser, 0, 2, 1, 1);

        pushButton_changePassword = new QPushButton(layoutWidget);
        pushButton_changePassword->setObjectName(QString::fromUtf8("pushButton_changePassword"));
        pushButton_changePassword->setFocusPolicy(Qt::NoFocus);
        pushButton_changePassword->setContextMenuPolicy(Qt::PreventContextMenu);

        gridLayout->addWidget(pushButton_changePassword, 0, 3, 1, 1);


        retranslateUi(dialog);

        QMetaObject::connectSlotsByName(dialog);
    } // setupUi

    void retranslateUi(QDialog *dialog)
    {
        dialog->setWindowTitle(QCoreApplication::translate("dialog", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\265\320\271 \320\220\320\240\320\234", nullptr));
        pushButton_addUser->setText(QCoreApplication::translate("dialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_editUser->setText(QCoreApplication::translate("dialog", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 ", nullptr));
        pushButton_deleteUser->setText(QCoreApplication::translate("dialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButton_changePassword->setText(QCoreApplication::translate("dialog", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialog: public Ui_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
