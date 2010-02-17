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
#include <QtGui/QFont>

#include "adderwidget.h"
#include "operationdialog.h"

AdderWidget::AdderWidget(const QString& caption, QWidget *parent)
	:QWidget(parent), m_caption(caption)
{
	updateToolTip();
}

void AdderWidget::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::darkGray);
	pen.setWidth(4);
	painter.setPen(pen);

	QRect m_rect(rect().x(), rect().top(), rect().width(), rect().height());

	//Shadow
	painter.drawLine(m_rect.x() + pen.width(), m_rect.y() + m_rect.height() - pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());
	painter.drawLine(m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());

	//Rect
	pen.setBrush(Qt::black);
	painter.setPen(pen);
	m_rect.setWidth(m_rect.width() - pen.width() * 2);
	m_rect.setHeight(m_rect.height() - pen.width() * 2);
	painter.drawRect(m_rect);

	//Fill rect
	m_rect.setX(m_rect.x() + pen.width() / 2);
	m_rect.setY(m_rect.y() + pen.width() / 2);
	painter.fillRect(m_rect, Qt::red);

	//Caption
	QFont m_font(font());
	m_font.setBold(true);
	m_font.setUnderline(true);
	painter.setFont(m_font);

	painter.drawText(m_rect.width() / 2 - fontMetrics().width(m_caption) / 2, 15, m_caption);
}

void AdderWidget::setFirstValue(const QByteArray& value)
{
	m_firstValue = value;
}

void AdderWidget::setSecondValue(const QByteArray& value)
{
	m_secondValue = value;
}

void AdderWidget::updateToolTip()
{
	setToolTip("<h1>" + m_caption + "</h1>");
}

void AdderWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
	if (ev->button() != Qt::LeftButton)
		return;

	OperationDialog d(this);
	d.exec();
}
