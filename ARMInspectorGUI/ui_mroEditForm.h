/********************************************************************************
** Form generated from reading UI file 'mroEditForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MROEDITFORM_H
#define UI_MROEDITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_mroEditForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditName;
    QComboBox *comboBoxInspection;

    void setupUi(QDialog *mroEditForm)
    {
        if (mroEditForm->objectName().isEmpty())
            mroEditForm->setObjectName(QString::fromUtf8("mroEditForm"));
        mroEditForm->resize(645, 276);
        mroEditForm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        buttonBox = new QDialogButtonBox(mroEditForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(240, 190, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(mroEditForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 60, 71, 16));
        label_2 = new QLabel(mroEditForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 120, 81, 16));
        lineEditName = new QLineEdit(mroEditForm);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setGeometry(QRect(160, 60, 431, 34));
        comboBoxInspection = new QComboBox(mroEditForm);
        comboBoxInspection->setObjectName(QString::fromUtf8("comboBoxInspection"));
        comboBoxInspection->setGeometry(QRect(160, 120, 431, 32));
        comboBoxInspection->setStyleSheet(QString::fromUtf8("QComboBox {\n"
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

        retranslateUi(mroEditForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), mroEditForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), mroEditForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(mroEditForm);
    } // setupUi

    void retranslateUi(QDialog *mroEditForm)
    {
        mroEditForm->setWindowTitle(QCoreApplication::translate("mroEditForm", "mroEditForm", nullptr));
        label->setText(QCoreApplication::translate("mroEditForm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("mroEditForm", "\320\230\320\275\321\201\320\277\320\265\320\272\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mroEditForm: public Ui_mroEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MROEDITFORM_H
