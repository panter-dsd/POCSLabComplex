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

#include "abstractblock.h"

AbstractBlock::AbstractBlock(const QString& caption, QWidget *parent)
	: QWidget(parent), m_caption(caption), m_isModule(false), m_operation(-1)
{
	updateToolTip();
}

void AbstractBlock::paintEvent(QPaintEvent */*ev*/)
{
	QPainter painter(this);

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::darkGray);
	pen.setWidth(5);
	painter.setPen(pen);

	QRect m_rect(rect().x(), rect().top(), rect().width(), rect().height());

	//Shadow
	painter.drawLine(m_rect.x() + pen.width(), m_rect.y() + m_rect.height(), m_rect.x() + m_rect.width(), m_rect.y() + m_rect.height());
	painter.drawLine(m_rect.x() + m_rect.width(), m_rect.y() + pen.width(), m_rect.x() + m_rect.width(), m_rect.y() + m_rect.height() - pen.width());

	//Rect
	pen.setBrush(Qt::black);
	painter.setPen(pen);
	m_rect.setWidth(m_rect.width() - pen.width());
	m_rect.setHeight(m_rect.height() - pen.width());
	painter.drawRect(m_rect);

	//Fill rect
	m_rect.setX(m_rect.x() + pen.width() / 2);
	m_rect.setY(m_rect.y() + pen.width() / 2);

	if (m_operation < 0)
		painter.fillRect(m_rect, Qt::red);
	else
		painter.fillRect(m_rect, Qt::green);

	//
	QPen smallPen(pen);
	smallPen.setWidth(1);
	painter.setPen(smallPen);
	painter.drawLine(rect().x() + rect().width() - pen.width(), rect().y() + rect().height() / 3, rect().x() + rect().width(), rect().y() + rect().height() / 3);
	painter.drawLine(rect().x() + rect().width() - pen.width(), rect().y() + rect().height() / 3 * 2, rect().x() + rect().width(), rect().y() + rect().height() / 3 * 2);

	//Caption
	QFont m_font(font());
	m_font.setBold(true);
	m_font.setUnderline(true);
	painter.setFont(m_font);

	painter.drawText(m_rect.width() / 2 - fontMetrics().width(m_caption) / 2,
					 m_rect.height() / 2 + fontMetrics().height() / 2, m_caption);
}

void AbstractBlock::setFirstValue(const QByteArray& value)
{
	m_firstValue = value;
}

void AbstractBlock::setSecondValue(const QByteArray& value)
{
	m_secondValue = value;
}

void AbstractBlock::mouseDoubleClickEvent(QMouseEvent */*ev*/)
{
	chooseOperation();
}

void AbstractBlock::updateToolTip()
{
	setToolTip("<h2 align=center><u>" + m_caption + "</u></h2>");
}
