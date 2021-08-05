/********************************************************************************
** Form generated from reading UI file 'RptColumnEditForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RPTCOLUMNEDITFORM_H
#define UI_RPTCOLUMNEDITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_RptColumnEditForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBoxArticle;
    QComboBox *comboBoxSubject;
    QLineEdit *lineEdit;

    void setupUi(QDialog *RptColumnEditForm)
    {
        if (RptColumnEditForm->objectName().isEmpty())
            RptColumnEditForm->setObjectName(QString::fromUtf8("RptColumnEditForm"));
        RptColumnEditForm->resize(703, 300);
        RptColumnEditForm->setToolTipDuration(-4);
        RptColumnEditForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"   border-radius: 8px;\n"
"   color: rgb(0, 93, 168);\n"
"   min-width: 170px;\n"
"   min-height: 30px;\n"
"   padding-left: 15px;\n"
"}\n"
"QComboBox:on {"
                        "\n"
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
        buttonBox = new QDialogButtonBox(RptColumnEditForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(RptColumnEditForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 71, 16));
        label_2 = new QLabel(RptColumnEditForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 120, 81, 16));
        label_3 = new QLabel(RptColumnEditForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 170, 111, 16));
        comboBoxArticle = new QComboBox(RptColumnEditForm);
        comboBoxArticle->setObjectName(QString::fromUtf8("comboBoxArticle"));
        comboBoxArticle->setGeometry(QRect(170, 50, 461, 32));
        comboBoxSubject = new QComboBox(RptColumnEditForm);
        comboBoxSubject->setObjectName(QString::fromUtf8("comboBoxSubject"));
        comboBoxSubject->setGeometry(QRect(170, 110, 461, 32));
        lineEdit = new QLineEdit(RptColumnEditForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(170, 170, 461, 34));

        retranslateUi(RptColumnEditForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), RptColumnEditForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RptColumnEditForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(RptColumnEditForm);
    } // setupUi

    void retranslateUi(QDialog *RptColumnEditForm)
    {
        RptColumnEditForm->setWindowTitle(QCoreApplication::translate("RptColumnEditForm", "RptColumnEditForm", nullptr));
        label->setText(QCoreApplication::translate("RptColumnEditForm", "\320\241\321\202\320\260\321\202\321\214\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("RptColumnEditForm", "\320\241\321\203\320\261\321\212\320\265\320\272\321\202", nullptr));
        label_3->setText(QCoreApplication::translate("RptColumnEditForm", "\320\235\320\276\320\274\320\265\321\200 \320\272\320\276\320\273\320\276\320\275\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RptColumnEditForm: public Ui_RptColumnEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RPTCOLUMNEDITFORM_H
