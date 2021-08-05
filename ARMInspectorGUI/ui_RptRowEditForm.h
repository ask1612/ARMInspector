/********************************************************************************
** Form generated from reading UI file 'RptRowEditForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RPTROWEDITFORM_H
#define UI_RPTROWEDITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RptRowEditForm
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_Npp;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_Formula;
    QLabel *label_4;
    QLineEdit *lineEdit_Row;
    QTextEdit *textEdit_Name;

    void setupUi(QDialog *RptRowEditForm)
    {
        if (RptRowEditForm->objectName().isEmpty())
            RptRowEditForm->setObjectName(QString::fromUtf8("RptRowEditForm"));
        RptRowEditForm->resize(586, 440);
        RptRowEditForm->setToolTipDuration(-4);
        RptRowEditForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"QLineEdit {\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 1px solid gray;\n"
"border-radius: 8px;\n"
" min-height: 30px;\n"
"}\n"
"\n"
"QTextEdit {\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 1px solid gray;\n"
"border-radius: 4px;\n"
" min-height: 30px;\n"
"}\n"
"\n"
"QComboBox {\n"
"   background: qlineargradient(\n"
"   x1:0, y1:0, x2:0, y2:1,\n"
"   stop:0 #f9f9f9,\n"
"   stop: 0.5 #c6c6c6,\n"
"   stop: 0.6 #dfdfdf,\n"
"   stop:1 #f9f9f9 );\n"
"   border-style: solid;\n"
"   border-width: 1px;\n"
"   border-color: rgb(0, 93, 168);\n"
"   bo"
                        "rder-radius: 8px;\n"
"   color: rgb(0, 93, 168);\n"
"   min-width: 170px;\n"
"   min-height: 30px;\n"
"   padding-left: 15px;\n"
"}\n"
"QComboBox:on {\n"
"   border-radius: 30px;\n"
"   background:transparent;\n"
"}\n"
"QComboBox::drop-down {\n"
"   image: url(:/bwt/downarrow.png);\n"
"   subcontrol-position: center right;\n"
"   margin-right: 10px;\n"
"}\n"
"QComboBox QAbstractItemView::item {\n"
"   padding: 10px 10px 10px 10px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"   color: rgb(0, 93, 168);\n"
"   background: transparent;\n"
"}\n"
"QComboBox QListView::item {\n"
"   background: qradialgradient(\n"
"   cx: 0.5, cy: -1.6, fx: 0.5, fy: 0,\n"
"   radius: 2,\n"
"   stop: 0 #C4C4C4,\n"
"   stop: 1 #DBDBDB );\n"
"   border-style: solid;\n"
"   border-width: 1px;\n"
"   border-color: rgb(0, 93, 168);\n"
"   border-radius: 20px;\n"
"}"));
        buttonBox = new QDialogButtonBox(RptRowEditForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(200, 350, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(RptRowEditForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 50, 511, 251));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_Npp = new QLineEdit(layoutWidget);
        lineEdit_Npp->setObjectName(QString::fromUtf8("lineEdit_Npp"));

        gridLayout->addWidget(lineEdit_Npp, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_Formula = new QLineEdit(layoutWidget);
        lineEdit_Formula->setObjectName(QString::fromUtf8("lineEdit_Formula"));

        gridLayout->addWidget(lineEdit_Formula, 2, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_Row = new QLineEdit(layoutWidget);
        lineEdit_Row->setObjectName(QString::fromUtf8("lineEdit_Row"));

        gridLayout->addWidget(lineEdit_Row, 3, 1, 1, 1);

        textEdit_Name = new QTextEdit(layoutWidget);
        textEdit_Name->setObjectName(QString::fromUtf8("textEdit_Name"));

        gridLayout->addWidget(textEdit_Name, 1, 1, 1, 1);


        retranslateUi(RptRowEditForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), RptRowEditForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RptRowEditForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(RptRowEditForm);
    } // setupUi

    void retranslateUi(QDialog *RptRowEditForm)
    {
        RptRowEditForm->setWindowTitle(QCoreApplication::translate("RptRowEditForm", "RptColumnEditForm", nullptr));
        label->setText(QCoreApplication::translate("RptRowEditForm", "\342\204\226 \320\277/\320\277", nullptr));
        label_2->setText(QCoreApplication::translate("RptRowEditForm", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("RptRowEditForm", "\320\244\320\276\321\200\320\274\321\203\320\273\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("RptRowEditForm", "\320\235\320\276\320\274\320\265\321\200 \321\201\321\202\321\200\320\276\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RptRowEditForm: public Ui_RptRowEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RPTROWEDITFORM_H
