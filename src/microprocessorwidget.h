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

#ifndef MICROPROCESSORWIDGET_H
#define MICROPROCESSORWIDGET_H

class QPainter;
class QAction;
class AbstractBlock;
class Alb1Block;
class Alb2Block;
class Alb3Block;
class Mb1Block;
class Mb2Block;

#include <QtGui/QWidget>

class MicroprocessorWidget : public QWidget
{
	Q_OBJECT

private:
	Alb1Block *alb1;
	Alb2Block *alb2;
	Alb3Block *alb3;
	Mb1Block *mb1;
	Mb2Block *mb2;

	QAction *actionChooseScheme;

	QRect m_workRect;
	char m_scheme;
	qint16 m_adjustingWord;
	QPoint inputPoints [6];
	QPoint outputPoints [6];
	QString inputCaptions [6];
	QString outputCaptions [6];

	QString m_name;

public:
	MicroprocessorWidget (QWidget *parent);
	virtual ~MicroprocessorWidget ()
	{}

	qint16 adjustingWord () const
	{ return m_adjustingWord; }
	void setAdjustingWord (qint16 m_adjustingWord);

	QString name ()
	{ return m_name; }

protected:
	void paintEvent (QPaintEvent *ev);
	void resizeEvent (QResizeEvent *ev);
	void updateWidgets ();

private:
	void paint_0 (QPaintEvent *ev, QPainter *painter);
	void resize_0 ();
	void paint_1 (QPaintEvent *ev, QPainter *painter);
	void resize_1 ();
	void paint_2 (QPaintEvent *ev, QPainter *painter);
	void resize_2 ();
	void retranslateStrings ();
	void setCaptions ();

protected:
	bool event (QEvent *ev);

private Q_SLOTS:
	void chooseScheme ();
	void updateAdjustingWorld ();

Q_SIGNALS:
	void nameChanged (const QString& name);
};

#endif //MICROPROCESSORWIDGET_H
