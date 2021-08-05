/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QMessageBoxEx.h
 * Author: kazun_as
 *
 * Created on 22 апреля 2021 г., 11:09
 */

#ifndef QMESSAGEBOXEX_H
#define QMESSAGEBOXEX_H
#include <QMessageBox>
class QMessageBoxEx : public QMessageBox
{
private:

	static QMap<QMessageBox::StandardButton, QString> m_customButtonNames;

protected:

	static void setCustomTextForButtons(QMessageBoxEx &msgBox);

public:

    QMessageBoxEx(QWidget *parent);

	static void setCustomTextForButton(QMessageBox::StandardButton button, const QString &text);

	static QMessageBox::StandardButton critical(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes ), QMessageBox::StandardButton defaultButton = NoButton);
	static QMessageBox::StandardButton information(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes ), QMessageBox::StandardButton defaultButton = NoButton);
	static QMessageBox::StandardButton question(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No), QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static QMessageBox::StandardButton warning(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes ), QMessageBox::StandardButton defaultButton = NoButton);

};


#endif /* QMESSAGEBOXEX_H */

