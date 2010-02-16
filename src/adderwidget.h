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

#ifndef ADDERWIDGET_H
#define ADDERWIDGET_H

class QLabel;

#include <QtGui/QWidget>

class AdderWidget : public QWidget {

	Q_OBJECT

private:
	QLabel *label;
	QString m_caption;
	QByteArray m_firstValue;
	QByteArray m_secondValue;

public:
	AdderWidget(const QString& caption = 0, QWidget *parent = 0);
	virtual ~AdderWidget()
	{}

	void setCaption(const QString& caption)
	{
		m_caption = caption;
		updateToolTip();
	}
	QString caption()
	{ return m_caption; }

protected:
	void paintEvent(QPaintEvent *ev);
	void mouseDoubleClickEvent(QMouseEvent *ev);


private:
	void updateToolTip();

public Q_SLOTS:
	void setFirstValue(const QByteArray& value);
	void setSecondValue(const QByteArray& value);

Q_SIGNALS:
	void valueChanged(const QByteArray& newValue);
};

#endif //ADDERWIDGET_H
