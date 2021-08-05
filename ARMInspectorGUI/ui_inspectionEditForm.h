/********************************************************************************
** Form generated from reading UI file 'inspectionEditForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTIONEDITFORM_H
#define UI_INSPECTIONEDITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_inspectionEditForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox;

    void setupUi(QDialog *inspectionEditForm)
    {
        if (inspectionEditForm->objectName().isEmpty())
            inspectionEditForm->setObjectName(QString::fromUtf8("inspectionEditForm"));
        inspectionEditForm->resize(703, 253);
        inspectionEditForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}"));
        buttonBox = new QDialogButtonBox(inspectionEditForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(270, 180, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(inspectionEditForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 131, 16));
        label_2 = new QLabel(inspectionEditForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 130, 131, 16));
        lineEdit = new QLineEdit(inspectionEditForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 60, 431, 34));
        comboBox = new QComboBox(inspectionEditForm);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(180, 120, 431, 32));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
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
"   border-style: so"
                        "lid;\n"
"   border-width: 1px;\n"
"   border-color: rgb(0, 93, 168);\n"
"   border-radius: 20px;\n"
"}"));

        retranslateUi(inspectionEditForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), inspectionEditForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), inspectionEditForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(inspectionEditForm);
    } // setupUi

    void retranslateUi(QDialog *inspectionEditForm)
    {
        inspectionEditForm->setWindowTitle(QCoreApplication::translate("inspectionEditForm", "inspectionEditForm", nullptr));
        label->setText(QCoreApplication::translate("inspectionEditForm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("inspectionEditForm", "\320\234\320\240\320\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class inspectionEditForm: public Ui_inspectionEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTIONEDITFORM_H
