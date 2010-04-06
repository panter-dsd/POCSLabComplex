/********************************************************************
* Copyright (C) PanteR
*-------------------------------------------------------------------
*
* POCSLabComplex is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* POCSLabComplex is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with POCSLabComplex if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA 02110-1301 USA
*-------------------------------------------------------------------
* Project:		POCSLabComplex
* Author:		PanteR
* Contact:		panter.dsd@gmail.com
*******************************************************************/

#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

class QComboBox;
class QLabel;
class QLineEdit;
class QSpinBox;

#include <QtGui/QDialog>

class InputDialog : public QDialog {
	Q_OBJECT

public:
	enum InputType {
		Hex,
		Dec
	};

private:
	QLabel *positiveChanelLabel;
	QLineEdit *positiveChanelEdit;
	QLabel *negativeChanelLabel;
	QLineEdit *negativeChanelEdit;
	QLabel *dizssLabel;

	QByteArray m_value;
public:
	InputDialog (QWidget *parent = 0);
	virtual ~InputDialog ()
	{}

	QByteArray value ();
	void setValue (const QByteArray& value);

private:
	void retranslateStrings();

protected:
	bool event(QEvent *ev);

private Q_SLOTS:
	void valueChanged ();
};


#endif //INPUTDIALOG_H
