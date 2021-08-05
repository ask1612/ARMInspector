/********************************************************************************
** Form generated from reading UI file 'docsAP.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCSAP_H
#define UI_DOCSAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_docsAP
{
public:

    void setupUi(QDialog *docsAP)
    {
        if (docsAP->objectName().isEmpty())
            docsAP->setObjectName(QString::fromUtf8("docsAP"));
        docsAP->resize(614, 328);

        retranslateUi(docsAP);

        QMetaObject::connectSlotsByName(docsAP);
    } // setupUi

    void retranslateUi(QDialog *docsAP)
    {
        docsAP->setWindowTitle(QCoreApplication::translate("docsAP", "docsAP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class docsAP: public Ui_docsAP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCSAP_H
