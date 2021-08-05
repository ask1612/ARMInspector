/********************************************************************************
** Form generated from reading UI file 'nsiEditForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NSIEDITFORM_H
#define UI_NSIEDITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_nsiEditForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelName;
    QLineEdit *lineEditName;

    void setupUi(QDialog *nsiEditForm)
    {
        if (nsiEditForm->objectName().isEmpty())
            nsiEditForm->setObjectName(QString::fromUtf8("nsiEditForm"));
        nsiEditForm->resize(400, 148);
        nsiEditForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"min-width: 50px;\n"
"max-width: 50px;\n"
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
        buttonBox = new QDialogButtonBox(nsiEditForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 80, 311, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelName = new QLabel(nsiEditForm);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(30, 40, 47, 13));
        lineEditName = new QLineEdit(nsiEditForm);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setGeometry(QRect(130, 30, 221, 34));

        retranslateUi(nsiEditForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), nsiEditForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), nsiEditForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(nsiEditForm);
    } // setupUi

    void retranslateUi(QDialog *nsiEditForm)
    {
        nsiEditForm->setWindowTitle(QCoreApplication::translate("nsiEditForm", "nsiEditForm", nullptr));
        labelName->setText(QCoreApplication::translate("nsiEditForm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nsiEditForm: public Ui_nsiEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NSIEDITFORM_H
