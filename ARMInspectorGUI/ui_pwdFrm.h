/********************************************************************************
** Form generated from reading UI file 'pwdFrm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PWDFRM_H
#define UI_PWDFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pwdFrm
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *labelPwd;
    QLineEdit *lineEditPwd;
    QLabel *labelPwd2;
    QLineEdit *lineEditPwd2;
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *labelUser;
    QLabel *labelUse1;

    void setupUi(QDialog *pwdFrm)
    {
        if (pwdFrm->objectName().isEmpty())
            pwdFrm->setObjectName(QString::fromUtf8("pwdFrm"));
        pwdFrm->setWindowModality(Qt::WindowModal);
        pwdFrm->resize(400, 263);
        pwdFrm->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"min-height: 15px;\n"
"max-height: 15px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #4169E1;     \n"
"}\n"
"\n"
"QLineEdit {\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 2px solid gray;\n"
"border-radius: 8px;\n"
"min-height:20px;\n"
"}\n"
""));
        layoutWidget = new QWidget(pwdFrm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 50, 351, 191));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelPwd = new QLabel(layoutWidget);
        labelPwd->setObjectName(QString::fromUtf8("labelPwd"));
        labelPwd->setLineWidth(-2);
        labelPwd->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(labelPwd, 0, 0, 1, 1);

        lineEditPwd = new QLineEdit(layoutWidget);
        lineEditPwd->setObjectName(QString::fromUtf8("lineEditPwd"));
        lineEditPwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        gridLayout->addWidget(lineEditPwd, 0, 1, 1, 1);

        labelPwd2 = new QLabel(layoutWidget);
        labelPwd2->setObjectName(QString::fromUtf8("labelPwd2"));

        gridLayout->addWidget(labelPwd2, 1, 0, 1, 1);

        lineEditPwd2 = new QLineEdit(layoutWidget);
        lineEditPwd2->setObjectName(QString::fromUtf8("lineEditPwd2"));
        lineEditPwd2->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        gridLayout->addWidget(lineEditPwd2, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);

        layoutWidget1 = new QWidget(pwdFrm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 10, 351, 40));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        labelUser = new QLabel(layoutWidget1);
        labelUser->setObjectName(QString::fromUtf8("labelUser"));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        labelUser->setFont(font);
        labelUser->setLayoutDirection(Qt::RightToLeft);
        labelUser->setStyleSheet(QString::fromUtf8("color:red;"));
        labelUser->setLineWidth(0);

        gridLayout_2->addWidget(labelUser, 1, 0, 1, 2);

        labelUse1 = new QLabel(layoutWidget1);
        labelUse1->setObjectName(QString::fromUtf8("labelUse1"));

        gridLayout_2->addWidget(labelUse1, 0, 0, 1, 1);


        retranslateUi(pwdFrm);
        QObject::connect(buttonBox, SIGNAL(rejected()), pwdFrm, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), pwdFrm, SLOT(accept()));

        QMetaObject::connectSlotsByName(pwdFrm);
    } // setupUi

    void retranslateUi(QDialog *pwdFrm)
    {
        pwdFrm->setWindowTitle(QCoreApplication::translate("pwdFrm", "\320\235\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        labelPwd->setText(QCoreApplication::translate("pwdFrm", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        labelPwd2->setText(QCoreApplication::translate("pwdFrm", "\320\237\320\260\321\200\320\276\320\273\321\214(\320\277\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214)", nullptr));
        labelUser->setText(QString());
        labelUse1->setText(QCoreApplication::translate("pwdFrm", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pwdFrm: public Ui_pwdFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PWDFRM_H
