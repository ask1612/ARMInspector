/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QMessageBoxEx.cpp
 * Author: kazun_as
 * 
 * Created on 22 апреля 2021 г., 11:09
 */

#include "QMessageBoxEx.h"
#include <QMap>


QMap<QMessageBox::StandardButton, QString> QMessageBoxEx::m_customButtonNames;

void QMessageBoxEx::setCustomTextForButton(QMessageBox::StandardButton button, const QString &text)
{
	if (m_customButtonNames.contains(button))
		m_customButtonNames.erase(m_customButtonNames.find(button));

	m_customButtonNames[button] = text;
}

void QMessageBoxEx::setCustomTextForButtons(QMessageBoxEx &msgBox)
{
	if (m_customButtonNames.size())
	{
		QMessageBox::StandardButtons buttons = msgBox.standardButtons();

		for (auto button : m_customButtonNames.keys())
		{
			if (buttons & button)
			{
				msgBox.setButtonText(button, m_customButtonNames[button]);
			}
		}
	}
}

QMessageBox::StandardButton QMessageBoxEx::critical(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
	QMessageBoxEx msgBox(parent);

	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle(title);
	msgBox.setText(text);
	msgBox.setStandardButtons(buttons);
	msgBox.setDefaultButton(defaultButton);

	setCustomTextForButtons(msgBox);

	return (QMessageBox::StandardButton)msgBox.exec();
}

QMessageBox::StandardButton QMessageBoxEx::information(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
	QMessageBoxEx msgBox(parent);

	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle(title);
	msgBox.setText(text);
	msgBox.setStandardButtons(buttons);
	msgBox.setDefaultButton(defaultButton);

	setCustomTextForButtons(msgBox);

	return (QMessageBox::StandardButton)msgBox.exec();
}

QMessageBox::StandardButton QMessageBoxEx::question(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
	QMessageBoxEx msgBox(parent);

	msgBox.setIcon(QMessageBox::Question);
	msgBox.setWindowTitle(title);
	msgBox.setText(text);
	msgBox.setStandardButtons(buttons);
	msgBox.setDefaultButton(defaultButton);

	setCustomTextForButtons(msgBox);

	return (QMessageBox::StandardButton)msgBox.exec();
}

QMessageBox::StandardButton QMessageBoxEx::warning(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
	QMessageBoxEx msgBox(parent);

	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setWindowTitle(title);
	msgBox.setText(text);
	msgBox.setStandardButtons(buttons);
	msgBox.setDefaultButton(defaultButton);

	setCustomTextForButtons(msgBox);

	return (QMessageBox::StandardButton)msgBox.exec();
}

QMessageBoxEx::QMessageBoxEx(QWidget *parent) : QMessageBox(parent)
{
	
}