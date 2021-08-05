/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAccount;
    QAction *action;
    QAction *actionListUsers;
    QAction *actionReport;
    QAction *actionExit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(839, 570);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QString::fromUtf8("QTableView {\n"
"         Color: white; /* text color in the table */\n"
"         Gridline-color: black; /*The inner frame color*/\n"
"         Background-color: rgb(108, 108, 108); /* background color in the table*/\n"
"    alternate-background-color: rgb(64, 64, 64);\n"
"         Selection-color: white; /* The text color of the selected area*/\n"
"         Selection-background-color: rgb(77, 77, 77); /*The background color of the selected area*/\n"
"    border: 2px groove gray;\n"
"    border-radius: 0px;\n"
"    padding: 2px 4px;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #646464;\n"
"    padding: 4px;\n"
"    border: 0px;\n"
"    font-size: 14pt;\n"
"}\n"
"QMenuBar {\n"
"  background-color:rgb(89,87,87);\n"
" min-width: 20px;\n"
" min-height: 20px;\n"
" }\n"
"QMenuBar::item {\n"
"     spacing: 3px; /* \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273 \320\274\320\265\320\266\320\264\321\203 \320\277\321\203\320\275\320\272\321\202\320\260\320\274\320\270 \320\274\320\265\320"
                        "\275\321\216 */\n"
"                     font-size: 10pt; \n"
"                     color: rgb(225,225,225);\n"
"                     border: 1px solid rgb(60,60,60);   \n"
"                     background-color:rgb(89,87,87);\n"
"                     padding:2px 2px; \n"
"                     margin:2px 2px;\n"
" }\n"
"\n"
" QMenuBar::item:selected { /* \320\272\320\276\320\263\320\264\320\260 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\276 \321\201 \320\277\320\276\320\274\320\276\321\211\321\214\321\216 \320\274\321\213\321\210\320\270 \320\270\320\273\320\270 \320\272\320\273\320\260\320\262\320\270\320\260\321\202\321\203\321\200\321\213 */\n"
"                     background-color:rgb(235,110,36);\n"
" }\n"
"\n"
" QMenuBar::item:pressed {\n"
"                                           border: 1px solid rgb(60,60,61); \n"
"                                           background-color: rgb(220,80,6);\n"
" }\n"
"QMenu {\n"
"                     background-color:rgb(89,87,87);\n"
"            "
                        "         border: 3px solid rgb(235,110,36);\n"
"                     }\n"
"                 QMenu::item {                    \n"
"                     font-size: 10pt; \n"
"                     color: rgb(225,225,225);\n"
"                     border: 3px solid rgb(60,60,60);   \n"
"                     background-color:rgb(89,87,87);\n"
"                     padding:6px 6px; \n"
"                     margin:2px 2px;\n"
"                      }\n"
"                QMenu::item:selected {\n"
"                     background-color:rgb(235,110,36);\n"
"                     }\n"
"                 QMenu::item:pressed {\n"
"                                           border: 1px solid rgb(60,60,61); \n"
"                                           background-color: rgb(220,80,6);\n"
"                                       }\n"
""));
        actionAccount = new QAction(MainWindow);
        actionAccount->setObjectName(QString::fromUtf8("actionAccount"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        actionListUsers = new QAction(MainWindow);
        actionListUsers->setObjectName(QString::fromUtf8("actionListUsers"));
        actionListUsers->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../xmlParser/images/information.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionListUsers->setIcon(icon);
        actionReport = new QAction(MainWindow);
        actionReport->setObjectName(QString::fromUtf8("actionReport"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionExit->setAutoRepeat(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 839, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setTearOffEnabled(false);
        menuFile->setToolTipsVisible(true);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionListUsers);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\220\320\240\320\234 \320\230\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        MainWindow->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\320\267\320\270\321\200\320\276\320\262\320\260\320\275\320\275\320\276\320\265 \321\200\320\260\320\261\320\276\321\207\320\265\320\265 \320\274\320\265\321\201\321\202\320\276 \320\270\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAccount->setText(QCoreApplication::translate("MainWindow", "Account", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202 \320\276\320\261 \320\220\320\237", nullptr));
        actionListUsers->setText(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217\320\274\320\270", nullptr));
#if QT_CONFIG(shortcut)
        actionListUsers->setShortcut(QCoreApplication::translate("MainWindow", "Alt+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReport->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\220\320\240\320\234 \320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
