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
#include <QtGui/QtEvents>

#include "switchboardwidget.h"
#include "switchboarddialog.h"

const int penWidth = 7;

SwitchboardWidget::SwitchboardWidget (QWidget *parent)
	: QWidget (parent)
{

}

void SwitchboardWidget::paintEvent (QPaintEvent *ev)
{
	QPainter painter (this);

	QPen pen;
	pen.setStyle (Qt::SolidLine);
	pen.setBrush (Qt::darkGray);
	pen.setWidth (penWidth);
	painter.setPen (pen);

	QRect m_rect (rect ().x (), rect ().top (), rect ().width (), rect ().height ());

	//Shadow
	painter.drawLine (m_rect.x () + pen.width (), m_rect.y () + m_rect.height () - pen.width (), m_rect.x () + m_rect.width () - pen.width (), m_rect.y () + m_rect.height () - pen.width ());
	painter.drawLine (m_rect.x () + m_rect.width () - pen.width (), m_rect.y () + pen.width (), m_rect.x () + m_rect.width () - pen.width (), m_rect.y () + m_rect.height () - pen.width ());

	//Rect
	pen.setBrush (Qt::black);
	painter.setPen (pen);
	m_rect.setWidth (m_rect.width () - penWidth * 2);
	m_rect.setHeight (m_rect.height () - penWidth * 2);
	painter.drawRect (m_rect);

	QRect m_workRect (rect ().x () + penWidth / 2, rect ().y () + penWidth / 2,
					  rect ().width () - penWidth / 2 - penWidth * 2, rect ().height () - penWidth / 2 - penWidth * 2);

	pen.setWidth (1);
	painter.setPen (pen);
	for (int i = 0; i < 6; i++) {
		inputPoints [i].setX (rect ().x () + penWidth / 2);
		inputPoints [i].setY (m_workRect.y () + m_workRect.height () / 6 * i + m_workRect.height () / 6 / 2);

		outputPoints [i].setX (m_workRect.x () + m_workRect.width ());
		outputPoints [i].setY (m_workRect.y () + m_workRect.height () / 6 * i + m_workRect.height () / 6 / 2);

		painter.drawLine (m_workRect.x () + m_workRect.width (), m_workRect.y () + m_workRect.height () / 6 * i + m_workRect.height () / 6 / 2,
						 rect ().width (), m_workRect.y () + m_workRect.height () / 6 * i + m_workRect.height () / 6 / 2);
	}

	QMapIterator <int, int> it (m_connections);
	while (it.hasNext ()) {
		it.next ();
		painter.drawLine (inputPoints [it.key ()], outputPoints  [it.value ()]);
	}
}

void SwitchboardWidget::setInputCaptions (const QStringList& captions)
{
	m_inputCaptions = captions;
}

void SwitchboardWidget::setOutputCaptions (const QStringList& captions)
{
	m_outputCaptions = captions;
}

QByteArray SwitchboardWidget::outputValue (int index) const
{ 
	const int i = m_connections.key (index, -1);
   
	return i != -1 ? m_inputValues [i] : QByteArray (); 
}

bool SwitchboardWidget::event (QEvent *ev)
{
	if (ev->type () == QEvent::MouseButtonDblClick) {
		setConnections ();
	}

	return QWidget::event (ev);
}


void SwitchboardWidget::setConnections ()
{
	SwitchboardDialog d (this);
	d.setInputCaptions (m_inputCaptions);
	d.setOutputCaptions (m_outputCaptions);
	d.setConnections (m_connections);

	if (d.exec ()) {
		m_connections = d.connections ();
	}
}
