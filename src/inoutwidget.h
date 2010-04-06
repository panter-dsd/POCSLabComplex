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

#ifndef INOUTWIDGET_H
#define INOUTWIDGET_H

class QLabel;

#include <QtGui/QWidget>

class InOutWidget : public QWidget {
	Q_OBJECT

public:
	enum Type {
		In = 0,
		Out
	};

private:
	int m_type;
	QByteArray m_values[6];
	QList<QLabel*> labels;
	int m_lastIndex;

public:
	InOutWidget (Type type, QWidget *parent = 0);
	virtual ~InOutWidget ()
	{}

protected:
	void paintEvent(QPaintEvent *ev);
	bool eventFilter(QObject *o, QEvent *ev);
};

#endif //INOUTWIDGET_H