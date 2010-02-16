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
#include <QtGui/QLabel>

#include "microprocessorwidget.h"

MicroprocessorWidget::MicroprocessorWidget(QWidget *parent)
	:QWidget(parent)
{
	setFixedSize(500, 300);

	alb1 = new QLabel(this);
	alb2 = new QLabel(this);
	alb3 = new QLabel(this);
	mb1 = new QLabel(this);
	mb2 = new QLabel(this);

	foreach(QLabel *label, findChildren<QLabel*> ()) {
		label->setFixedSize(100, 40);
		label->setFrameShape(QFrame::Box);
		label->setAlignment(Qt::AlignTop);
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

	QRect m_rect(rect());
	m_rect.setX(m_rect.x() + 20);
	m_rect.setWidth(m_rect.width() - 20);

	painter.drawLine(m_rect.x() + pen.width(), m_rect.y() + m_rect.height() - pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());
	painter.drawLine(m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());

	pen.setBrush(Qt::black);
	painter.setPen(pen);
	m_rect.setWidth(m_rect.width() - pen.width() * 2);
	m_rect.setHeight(m_rect.height() - pen.width() * 2);
	painter.drawRect(m_rect);


	paint_1(ev, &painter);
}

void MicroprocessorWidget::paint_1(QPaintEvent *ev, QPainter *painter)
{
	alb1->move(width() / 2 - alb1->width() / 2, 40);
	alb2->move(width() / 2 - alb1->width() / 2, height() / 2 + alb2->height() / 2);
	alb3->move(width() - alb3->width() - 60, 20 + alb1->height());
	mb1->move(60, height() / 2 - mb1->height() / 2);
	mb2->move(60, height() / 2 + mb1->height() / 2 + 40);

	alb1->setText("<p align=center><span style=\" text-decoration: underline;\">" + tr("ALB1") + "</span style></p>");
	alb2->setText("<p align=center><span style=\" text-decoration: underline;\">" + tr("ALB2") + "</span style></p>");
	alb3->setText("<p align=center><span style=\" text-decoration: underline;\">" + tr("ALB3") + "</span style></p>");
	mb1->setText("<p align=center><span style=\" text-decoration: underline;\">" + tr("MB1") + "</span style></p>");
	mb2->setText("<p align=center><span style=\" text-decoration: underline;\">" + tr("MB2") + "</span style></p>");


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
