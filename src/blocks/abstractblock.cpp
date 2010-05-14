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
#include <QtGui/QAction>

#include "abstractblock.h"
#include "operations.h"
#include "reportdialog.h"

AbstractBlock::AbstractBlock (const QString& caption, QWidget *parent)
	: QWidget (parent), m_caption (caption), m_isModule (false), m_operation (-1)
{
	actionChooseOperation = new QAction (this);
	connect (actionChooseOperation, SIGNAL (triggered ()), this, SLOT (chooseOperation ()));
	addAction (actionChooseOperation);

	actionShowReport = new QAction (this);
	connect (actionShowReport, SIGNAL (triggered ()), this, SLOT (showReport ()));
	addAction (actionShowReport);

	setContextMenuPolicy (Qt::ActionsContextMenu);
	updateToolTip ();
	retranslateStrings ();
}

void AbstractBlock::retranslateStrings ()
{
	actionChooseOperation->setText (tr ("Choose operation"));
	actionShowReport->setText (tr ("Show report"));
}

void AbstractBlock::paintEvent (QPaintEvent */*ev*/)
{
	QPainter painter (this);

	QPen pen;
	pen.setStyle (Qt::SolidLine);
	pen.setBrush (Qt::darkGray);
	pen.setWidth (5);
	painter.setPen (pen);

	QRect m_rect (rect ().x (), rect ().top (), rect ().width (), rect ().height ());

	//Shadow
	painter.drawLine (m_rect.x () + pen.width (), m_rect.y () + m_rect.height (), m_rect.x () + m_rect.width (), m_rect.y () + m_rect.height ());
	painter.drawLine (m_rect.x () + m_rect.width (), m_rect.y () + pen.width (), m_rect.x () + m_rect.width (), m_rect.y () + m_rect.height () - pen.width ());

	//Rect
	pen.setBrush (Qt::black);
	painter.setPen (pen);
	m_rect.setWidth (m_rect.width () - pen.width ());
	m_rect.setHeight (m_rect.height () - pen.width ());
	painter.drawRect (m_rect);

	//Fill rect
	m_rect.setX (m_rect.x () + pen.width () / 2);
	m_rect.setY (m_rect.y () + pen.width () / 2);

	if (m_operation < 0)
		painter.fillRect (m_rect, Qt::red);
	else
		painter.fillRect (m_rect, Qt::green);

	//
	QPen smallPen (pen);
	smallPen.setWidth (1);
	painter.setPen (smallPen);
	painter.drawLine (rect ().x () + rect ().width () - pen.width (), rect ().y () + rect ().height () / 3, rect ().x () + rect ().width (), rect ().y () + rect ().height () / 3);
	painter.drawLine (rect ().x () + rect ().width () - pen.width (), rect ().y () + rect ().height () / 3 * 2, rect ().x () + rect ().width (), rect ().y () + rect ().height () / 3 * 2);

	//Caption
	QFont m_font (font ());
	m_font.setBold (true);
	m_font.setUnderline (true);
	painter.setFont (m_font);

	painter.drawText (m_rect.width () / 2 - fontMetrics ().width (m_caption) / 2,
					 m_rect.height () / 2 + fontMetrics ().height () / 2, m_caption);
}

void AbstractBlock::setFirstValue (const QByteArray& value)
{
	m_firstValue = value;
	updateToolTip ();
}

void AbstractBlock::setSecondValue (const QByteArray& value)
{
	m_secondValue = value;
	updateToolTip ();
}

void AbstractBlock::updateToolTip ()
{
	QString m_toolTip = "<h2 align=center><u>" + m_caption + "</u></h2>";

	if (m_operation >= 0) {
		m_toolTip += "<p><b>";
		m_toolTip += tr ("Current operation");
		m_toolTip += "</b>: ";
		if (m_isModule)
			m_toolTip += moduleOperations.value (m_operation);
		else
			m_toolTip += operations.value (m_operation);
		m_toolTip += "</p>";
	}

	m_toolTip += "<p><b>";
	m_toolTip += tr ("First value");
	m_toolTip += "</b>: ";
	m_toolTip += Operations::binToHtmlString (m_firstValue);
	m_toolTip += "</p>";

	m_toolTip += "<p><b>";
	m_toolTip += tr ("Second value");
	m_toolTip += "</b>: ";
	m_toolTip += Operations::binToHtmlString (m_secondValue);
	m_toolTip += "</p>";

	m_toolTip += "<p><b>";
	m_toolTip += tr ("Result");
	m_toolTip += "</b>: ";
	m_toolTip += Operations::binToHtmlString (m_calculatedValue);
	m_toolTip += "</p>";

	setToolTip (m_toolTip);
}

bool AbstractBlock::event (QEvent *ev)
{
	if (ev->type () == QEvent::MouseButtonDblClick) {
		chooseOperation ();
	}
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QWidget::event (ev);
}

void AbstractBlock::showReport ()
{
	updateToolTip ();

	ReportDialog d (toolTip () + m_report, this);
	d.exec ();
}
