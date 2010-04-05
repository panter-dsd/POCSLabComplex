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
#include <QtGui/QMouseEvent>

#include "inoutwidget.h"

const int penWidth = 7;

InOutWidget::InOutWidget (Type type, QWidget *parent)
	: QWidget (parent), m_type (type), m_lastIndex (-1)
{
	setMouseTracking(true);
}

void InOutWidget::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::darkGray);
	pen.setWidth(penWidth);
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

	workRect.setRect (rect().x() + pen.width(), rect().top() + pen.width(),
					rect().width() - pen.width() * 2, rect().height() - pen.width() * 2);

	QPen smallPen;
	smallPen.setStyle(Qt::SolidLine);
	smallPen.setBrush(Qt::black);
	smallPen.setWidth(1);
	painter.setPen(smallPen);

	for (int i = 1; i < 6; i++) {
		painter.drawLine(workRect.x(), workRect.height() / 6 * i, workRect.width(), workRect.height() / 6 * i);
		if (m_type == In) {
			painter.drawLine(workRect.width(), workRect.height() / 6 * i - workRect.height() / 6 / 2, rect ().width(), workRect.height() / 6 * i - workRect.height() / 6 / 2);
		}
	}
	if (m_type == In) {
		painter.drawLine(workRect.width(), workRect.height() - workRect.height() / 6 / 2, rect ().width(), workRect.height() - workRect.height() / 6 / 2);
	}
}

void InOutWidget::mouseDoubleClickEvent (QMouseEvent *ev)
{
	int index = indexFromPos (ev->pos());
	if (index < 0)
		return;
}

void InOutWidget::mouseMoveEvent(QMouseEvent *ev)
{
	int index = indexFromPos (ev->pos());

	if (index >= 0 && m_lastIndex != index) {
		m_lastIndex = index;
		updateToolTip ();
	}
}

inline int InOutWidget::indexFromPos (const QPoint& pos) const
{
	int index = -1;
	for (int i = 0; i < 6; i++) {
		if (pos.y() > workRect.height() / 6 * i && pos.y() < workRect.height() / 6 * (i + 1)) {
			index = i;
			break;
		}
	}
	return index;
}

void InOutWidget::updateToolTip ()
{
	static const QString m_toolTip = "<b>Dec:</b> %1 \n<b>Hex:</b> %2\n<b>Bin:</b> %3";
	setToolTip(m_toolTip.arg(m_values[m_lastIndex]));
}
