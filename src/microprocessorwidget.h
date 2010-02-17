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
class AdderWidget;

#include <QtGui/QWidget>

class MicroprocessorWidget : public QWidget {

	Q_OBJECT

private:
	AdderWidget *alb1;
	AdderWidget *alb2;
	AdderWidget *alb3;
	AdderWidget *mb1;
	AdderWidget *mb2;

public:
	MicroprocessorWidget(QWidget *parent);
	virtual ~MicroprocessorWidget()
	{}

protected:
	void paintEvent(QPaintEvent *ev);

private:
	void paint_1(QPaintEvent *ev, QPainter *painter);

};

#endif //MICROPROCESSORWIDGET_H
