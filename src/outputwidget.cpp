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

#include <QtCore/QDataStream>

#include <QtGui/QPainter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QtEvents>
#include <QtGui/QMenu>
#include <QtGui/QAction>

#include "outputwidget.h"
#include "inputdialog.h"
#include "operations.h"

const int penWidth = 7;

OutputWidget::OutputWidget (QWidget *parent)
	: QWidget (parent), m_scaleFactor (0)
{
	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->setContentsMargins (penWidth / 2, penWidth / 2, penWidth * 2, penWidth * 2);
	mainLayout->setSpacing (0);

	for (int i = 0; i < 6; i++) {
		QLabel *label = new QLabel (this);
		label->setFrameShape (QFrame::Box);
		label->installEventFilter (this);
		label->setContextMenuPolicy (Qt::CustomContextMenu);
		label->setEnabled (false);

		mainLayout->addWidget (label);
		labels.append (label);
	}
	setLayout (mainLayout);

	retranslateStrings ();
}

void OutputWidget::retranslateStrings ()
{
}

bool OutputWidget::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QWidget::event (ev);
}

void OutputWidget::paintEvent (QPaintEvent */*ev*/)
{
	QPainter painter (this);

	QPen pen;
	pen.setStyle (Qt::SolidLine);
	pen.setBrush (Qt::darkGray);
	pen.setWidth (penWidth);
	painter.setPen (pen);

	QRect m_rect (rect ().x (), rect ().y (), rect ().width (), rect ().height ());

	//Shadow
	painter.drawLine (m_rect.x () + pen.width (), m_rect.y () + m_rect.height () - pen.width (), m_rect.x () + m_rect.width () - pen.width (), m_rect.y () + m_rect.height () - pen.width ());
	painter.drawLine (m_rect.x () + m_rect.width () - pen.width (), m_rect.y () + pen.width (), m_rect.x () + m_rect.width () - pen.width (), m_rect.y () + m_rect.height () - pen.width ());

	//Rect
	pen.setBrush (Qt::black);
	painter.setPen (pen);
	m_rect.setWidth (m_rect.width () - pen.width () * 2);
	m_rect.setHeight (m_rect.height () - pen.width () * 2);
	painter.drawRect (m_rect);

	pen.setWidth (1);
	painter.setPen (pen);
}

bool OutputWidget::eventFilter (QObject *o, QEvent *ev)
{
	return QWidget::eventFilter (0, ev);
}

void OutputWidget::setInputCaptions (const QStringList& captions)
{
	for (int i = 0; i < 6; i++) {
		m_captions [i] = captions.at (i);
		labels [i]->setEnabled (!m_captions [i].isEmpty ());
	}
	updateLabelsText ();
}

void OutputWidget::updateLabelsText ()
{
	for (int i = 0; i < 6; i++) {
		const QString caption = m_captions [i];
		if (!m_values [i].isEmpty () && labels [i]->isEnabled ()) {
			QByteArray tmp (m_values [i]);

			if (m_scaleFactor) {
				tmp.insert (0, '.');
				tmp.insert (0, (char) 0);
			} else {
				tmp.insert (m_scaleFactor, '.');
				while (tmp [1] != '.') {
					tmp.remove (0, 1);
				}
			}

			QString text = "<p> " + caption + " =  " + Operations::binToString (tmp) + "  </p>";
			text = text.replace ("-1", "<span style=\"text-decoration: overline\">1</span>");
			labels [i]->setText (text);
			labels [i]->setToolTip (text);
			labels [i]->setAlignment (Qt::AlignLeft | Qt::AlignBottom);
		} else {
			labels [i]->setAlignment (Qt::AlignCenter | Qt::AlignBottom);
			if (labels [i]->isEnabled ()) {
				labels [i]->setText (caption);
			} else {
				labels [i]->setText ("X");
			}
		}
	}
}

void OutputWidget::setValue (int index, const QByteArray& value)
{
	m_values [index] = value;
	updateLabelsText ();
}

QByteArray OutputWidget::saveState () const
{
	QByteArray state;

	QDataStream stream (&state, QIODevice::WriteOnly);

	for (int i = 0; i < 6; i++) {
		stream << m_values [i];
	}

	return state;
}

void OutputWidget::restoreState (QByteArray state)
{
	QDataStream stream (&state, QIODevice::ReadOnly);

	for (int i = 0; i < 6; i++) {
		stream >> m_values [i];
	}

	updateLabelsText ();
}

void OutputWidget::setScaledFactor (int scaledFactor)
{
	m_scaleFactor = scaledFactor;
	updateLabelsText ();
}
