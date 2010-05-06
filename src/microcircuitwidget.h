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

#ifndef MICROCIRCUITWIDGET_H
#define MICROCIRCUITWIDGET_H

class InOutWidget;
class SwitchboardWidget;
class MicroprocessorWidget;
class QLabel;

#include <QtGui/QWidget>

class MicrocircuitWidget : public QWidget {
	Q_OBJECT

private:
	QLabel *inputLabel;
	QLabel *inputSwitchboardLabel;
	QLabel *microprocessorLabel;
	QLabel *outputLabel;

	InOutWidget *inputInOut;
	SwitchboardWidget *inputSwitchboard;
	MicroprocessorWidget *microprocessor;
	InOutWidget *outputInOut;

public:
	MicrocircuitWidget (QWidget *parent = 0);
	virtual ~MicrocircuitWidget ()
	{}

protected:
	bool event (QEvent *ev);

private:
	void retranslateStrings ();

private Q_SLOTS:
	void microprocessorNameChanged (const QString& name);
	void microprocessorSchemeChanged ();
};

#endif //MICROCIRCUITWIDGET_H
