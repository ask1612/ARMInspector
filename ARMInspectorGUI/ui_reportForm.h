/********************************************************************************
** Form generated from reading UI file 'reportForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTFORM_H
#define UI_REPORTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reportForm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Data;
    QDateEdit *dateEdit;
    QLabel *label_Period;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QPushButton *pushButton_Report;
    QPushButton *pushButton_Excel;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTableView *tableView;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QTableView *tableView_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QTableView *tableView_3;
    QWidget *tab_4;
    QGridLayout *gridLayout;
    QTableView *tableView_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *reportForm)
    {
        if (reportForm->objectName().isEmpty())
            reportForm->setObjectName(QString::fromUtf8("reportForm"));
        reportForm->resize(1393, 600);
        centralwidget = new QWidget(reportForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_Data = new QLabel(centralwidget);
        label_Data->setObjectName(QString::fromUtf8("label_Data"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_Data->sizePolicy().hasHeightForWidth());
        label_Data->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_Data);

        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setEnabled(true);
        sizePolicy.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy);
        dateEdit->setMaximumSize(QSize(16777213, 16777214));
        dateEdit->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"	border: 2px solid lightgray;\n"
"	border-radius: 8px;\n"
"	height: 30px;\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"	subcontrol-origin: padding;\n"
"	subcontrol-position: top right;\n"
"	width: 25px;\n"
"\n"
"	border-left-width: 1px;\n"
"	border-left-color: darkgray;\n"
"	border-left-style: solid;\n"
"	border-top-right-radius: 3px;\n"
"	border-bottom-right-radius: 3px;\n"
"}\n"
"\n"
"QDateEdit::down-arrow {\n"
"	image: url(Icons/combobox_down_arrow1.png);\n"
"}\n"
"\n"
"QDateEdit::drop-down:hover {\n"
"	/* Does this work with QDateEdit??? */\n"
"	background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d8d7d7, stop: 1 #e9e9e9);\n"
"}\n"
""));
        dateEdit->setWrapping(false);
        dateEdit->setFrame(true);
        dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateEdit->setProperty("showGroupSeparator", QVariant(true));
        dateEdit->setDateTime(QDateTime(QDate(2021, 1, 1), QTime(0, 0, 0)));
        dateEdit->setCurrentSection(QDateTimeEdit::MonthSection);
        dateEdit->setCalendarPopup(true);

        horizontalLayout->addWidget(dateEdit);

        label_Period = new QLabel(centralwidget);
        label_Period->setObjectName(QString::fromUtf8("label_Period"));
        sizePolicy.setHeightForWidth(label_Period->sizePolicy().hasHeightForWidth());
        label_Period->setSizePolicy(sizePolicy);
        label_Period->setMaximumSize(QSize(16777215, 16777211));

        horizontalLayout->addWidget(label_Period);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(323, 0));
        groupBox->setMaximumSize(QSize(16777215, 16777211));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"    border: 2px solid gray;\n"
"    border-radius: 5px;\n"
"    margin-top: 1ex; /* leave space at the top for the title */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center; /* position at the top center */\n"
"    padding: 0 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"}\n"
"\n"
""));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 10, 52, 17));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(80, 10, 65, 17));
        radioButton_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"    border: 2px solid gray;\n"
"    border-radius: 5px;\n"
"    margin-top: 1ex; /* leave space at the top for the title */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center; /* position at the top center */\n"
"    padding: 0 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FFOECE, stop: 1 #FFFFFF);\n"
"}\n"
"\n"
""));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(150, 10, 97, 17));

        horizontalLayout->addWidget(groupBox);

        pushButton_Report = new QPushButton(centralwidget);
        pushButton_Report->setObjectName(QString::fromUtf8("pushButton_Report"));
        sizePolicy.setHeightForWidth(pushButton_Report->sizePolicy().hasHeightForWidth());
        pushButton_Report->setSizePolicy(sizePolicy);
        pushButton_Report->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"min-height: 30px;\n"
"max-height: 30px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #4169E1;     \n"
"}\n"
""));
        pushButton_Report->setFlat(true);

        horizontalLayout->addWidget(pushButton_Report);

        pushButton_Excel = new QPushButton(centralwidget);
        pushButton_Excel->setObjectName(QString::fromUtf8("pushButton_Excel"));
        pushButton_Excel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"min-height: 30px;\n"
"max-height: 30px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #4169E1;     \n"
"}\n"
"\n"
""));

        horizontalLayout->addWidget(pushButton_Excel);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        gridLayout_5->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableView = new QTableView(tab);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_2->addWidget(tableView, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableView_2 = new QTableView(tab_2);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));

        gridLayout_3->addWidget(tableView_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tableView_3 = new QTableView(tab_3);
        tableView_3->setObjectName(QString::fromUtf8("tableView_3"));

        gridLayout_4->addWidget(tableView_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout = new QGridLayout(tab_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView_4 = new QTableView(tab_4);
        tableView_4->setObjectName(QString::fromUtf8("tableView_4"));

        gridLayout->addWidget(tableView_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        gridLayout_5->addWidget(tabWidget, 1, 0, 1, 2);

        reportForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(reportForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1393, 21));
        reportForm->setMenuBar(menubar);
        statusbar = new QStatusBar(reportForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        reportForm->setStatusBar(statusbar);

        retranslateUi(reportForm);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(reportForm);
    } // setupUi

    void retranslateUi(QMainWindow *reportForm)
    {
        reportForm->setWindowTitle(QCoreApplication::translate("reportForm", "reportForm", nullptr));
        label_Data->setText(QCoreApplication::translate("reportForm", "\320\264\320\260\321\202\320\260", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("reportForm", "MM.yyyy", nullptr));
        label_Period->setText(QCoreApplication::translate("reportForm", "\320\237\320\265\321\200\320\270\320\276\320\264", nullptr));
        groupBox->setTitle(QString());
        radioButton->setText(QCoreApplication::translate("reportForm", "\320\274\320\265\321\201\321\217\321\206", nullptr));
        radioButton_2->setText(QCoreApplication::translate("reportForm", "\320\272\320\262\320\260\321\200\321\202\320\260\320\273", nullptr));
        radioButton_3->setText(QCoreApplication::translate("reportForm", " \321\201 \320\275\320\260\321\207\320\260\320\273\320\260 \320\263\320\276\320\264\320\260", nullptr));
        pushButton_Report->setText(QCoreApplication::translate("reportForm", "\320\241\321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\276\321\202\321\207\321\221\321\202", nullptr));
        pushButton_Excel->setText(QCoreApplication::translate("reportForm", "\320\222\321\213\320\263\321\203\320\267\320\270\321\202\321\214 \320\262 EXCEL", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("reportForm", "\320\244\320\270\320\273\320\270\320\260\320\273", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("reportForm", "\320\221\321\200\320\265\321\201\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("reportForm", "\320\221\320\260\321\200\320\260\320\275\320\276\320\262\320\270\321\207\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("reportForm", "\320\237\320\270\320\275\321\201\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reportForm: public Ui_reportForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTFORM_H
