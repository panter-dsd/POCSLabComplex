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

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QPen>

#include "microprocessorwidget.h"
#include "adderwidget.h"

MicroprocessorWidget::MicroprocessorWidget(QWidget *parent)
	:QWidget(parent)
{
	setFixedSize(600, 300);

	alb1 = new AdderWidget(tr("ALB1"), this);
	alb2 = new AdderWidget(tr("ALB2"), this);
	alb3 = new AdderWidget(tr("ALB3"), this);
	mb1 = new AdderWidget(tr("MB1"), this);
	mb2 = new AdderWidget(tr("MB2"), this);

	foreach(AdderWidget *label, findChildren<AdderWidget*> ()) {
		label->setFixedSize(width() / 5, height() / 5);
	}
}

void MicroprocessorWidget::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::darkGray);
	pen.setWidth(7);
	painter.setPen(pen);

	QRect m_rect(rect().x() + 20, rect().top(), rect().width() - 20, rect().height());

	//Shadow
	painter.drawLine(m_rect.x() + pen.width(), m_rect.y() + m_rect.height() - pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());
	painter.drawLine(m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());

	//Rect
	pen.setBrush(Qt::black);
	painter.setPen(pen);
	m_rect.setWidth(m_rect.width() - pen.width() * 2);
	m_rect.setHeight(m_rect.height() - pen.width() * 2);
	painter.drawRect(m_rect);


	paint_1(ev, &painter);
}

void MicroprocessorWidget::paint_1(QPaintEvent */*ev*/, QPainter *painter)
{
	alb1->move(width() / 2 - alb1->width() / 2, 20);
	alb2->move(width() / 2 - alb1->width() / 2, height() / 2 + alb2->height() / 2);
	alb3->move(width() - alb3->width() - 60, alb1->y() + alb1->height());
	mb1->move(60, height() / 2 - mb1->height() / 2);
	mb2->move(60, height() / 2 + mb1->height() / 2 + 40);

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);


	painter->drawLine(0, alb1->y() + alb1->height() / 3, alb1->x(), alb1->y() + alb1->height() / 3);
	painter->drawLine(0, alb1->y() + alb1->height() / 3 * 2, alb1->x(), alb1->y() + alb1->height() / 3 * 2);

	painter->drawLine(0, mb1->y() + mb1->height() / 3, mb1->x(), mb1->y() + mb1->height() / 3);
	painter->drawLine(0, mb1->y() + mb1->height() / 3 * 2, mb1->x(), mb1->y() + mb1->height() / 3 * 2);

	painter->drawLine(0, mb2->y() + mb2->height() / 3, mb2->x(), mb2->y() + mb2->height() / 3);
	painter->drawLine(0, mb2->y() + mb2->height() / 3 * 2, mb2->x(), mb2->y() + mb2->height() / 3 * 2);

}
