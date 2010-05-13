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

#include "inoutwidget.h"
#include "inputdialog.h"
#include "operations.h"

const int penWidth = 7;

InOutWidget::InOutWidget (Type type, QWidget *parent)
	: QWidget (parent), m_type (type), actionChangeValue (0), m_scaleFactor (0)
{
	setMouseTracking (true);

	if (m_type == In) {
		actionChangeValue = new QAction (this);
		connect (actionChangeValue, SIGNAL (triggered ()), this, SLOT (changeValue ()));
	}

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->setContentsMargins (penWidth / 2, penWidth / 2, penWidth * 2, penWidth * 2);
	mainLayout->setSpacing (0);

	for (int i = 0; i < 6; i++) {
		QLabel *label = new QLabel (this);
		label->setFrameShape (QFrame::Box);
		label->installEventFilter (this);
		label->setContextMenuPolicy (Qt::CustomContextMenu);

		mainLayout->addWidget (label);
		labels.append (label);
	}
	setLayout (mainLayout);
	setCount (0);

	retranslateStrings ();
}

void InOutWidget::retranslateStrings ()
{
	if (actionChangeValue)
		actionChangeValue->setText (tr ("Change value"));
}

bool InOutWidget::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QWidget::event (ev);
}

void InOutWidget::paintEvent (QPaintEvent */*ev*/)
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

	if (m_type == In) {
		for (int i = 0; i < 6; i++) {
			painter.drawLine (labels [i]->x () + labels [i]->width (), labels [i]->y () + labels [i]->height () / 2,
							 width (), labels [i]->y () + labels [i]->height () / 2);
		}
	}
}

bool InOutWidget::eventFilter (QObject *o, QEvent *ev)
{
	if (m_type == In) {
		if (ev->type () == QEvent::MouseButtonDblClick) {
			QLabel *label = qobject_cast<QLabel*> (o);
			if (label->isEnabled ()) {
				actionChangeValue->setParent (label);
				actionChangeValue->trigger ();
			}
		}

		if (ev->type () == QEvent::ContextMenu) {
			QContextMenuEvent *contextEvent = static_cast<QContextMenuEvent*> (ev);
			QLabel *label = qobject_cast<QLabel*> (o);
			QMenu menu;
			if (label->isEnabled ()) {
				actionChangeValue->setParent (label);
				menu.addAction (actionChangeValue);
				menu.exec (label->mapToGlobal (contextEvent->pos ()));
			}
		}
	}

	return QWidget::eventFilter (0, ev);
}

void InOutWidget::changeValue ()
{
	QAction *action = qobject_cast<QAction*> (sender ());
	if (!action)
		return;

	QLabel *label = qobject_cast<QLabel*> (action->parent ());
	if (label) {
		const int index = labels.indexOf (label);

		InputDialog d (this);
		d.setValue (m_values [index]);

		if (d.exec ()) {
			m_values [index] = d.value ();
			updateScaledFactor ();
			updateLabelsText ();
		}
	}
}

void InOutWidget::setCount (int count)
{
	m_count = count;

	for (int i = 0; i < labels.size (); i++) {
		labels [i]->setEnabled (i < m_count);
	}
	updateLabelsText ();
}

void InOutWidget::setInputCaptions (const QStringList& captions)
{
	for (int i = 0; i < 6; i++) {
		m_captions [i] = captions.at (i);
		labels [i]->setEnabled (!m_captions [i].isEmpty ());
	}
	updateLabelsText ();
}

bool InOutWidget::isValid () const
{
	for (int i = 0; i < m_count; i++) {
		if (m_values [i].isEmpty ()) {
			return false;
		}
	}

	return true;
}

void InOutWidget::updateLabelsText ()
{
	for (int i = 0; i < 6; i++) {
		const QString caption = m_type == In ? QString("A%1").arg (i) : m_captions [i];
		if (!m_values [i].isEmpty () && labels [i]->isEnabled ()) {
			QString text = "<p> " + caption + " =  " + Operations::binToString (m_values [i]) + " / " + QString::number (m_scaleFactor * 2) + "  </p>";
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

QStringList InOutWidget::outputCaptions () const
{
	QStringList l;
	for (int i = 0, count = labels.size (); i < count; i++) {
		l.append (labels [i]->isEnabled () ? QString ("A%1").arg (i) : "");
	}
	return l;
}

void InOutWidget::setValue (int index, const QByteArray& value)
{
	m_values [index] = value;
	updateScaledFactor ();
	updateLabelsText ();
}

QByteArray InOutWidget::saveState () const
{
	QByteArray state;

	QDataStream stream (&state, QIODevice::WriteOnly);

	for (int i = 0; i < 6; i++) {
		stream << m_values [i];
	}

	return state;
}

void InOutWidget::restoreState (QByteArray state)
{
	QDataStream stream (&state, QIODevice::ReadOnly);

	for (int i = 0; i < 6; i++) {
		stream >> m_values [i];
	}

	updateScaledFactor ();
	updateLabelsText ();
}

void InOutWidget::setScaledFactor (int scaledFactor)
{
	m_scaleFactor = scaledFactor;
	sendValues ();
}

void InOutWidget::updateScaledFactor ()
{
	m_scaleFactor = 0;
	for (int i = 0; i < m_count; i++) {
		if (!m_values [i].isEmpty () && m_values [i] [0] != (char) 0) {
			m_scaleFactor = 1;
			break;
		}
	}
	emit scaledFactorChanged (m_scaleFactor);
	sendValues ();
}

void InOutWidget::sendValues ()
{
	for (int i = 0; i < m_count; i++) {
		if (!m_values [i].isEmpty ()) {
			QByteArray tmp (m_values [i]);
			tmp.remove (tmp.indexOf ('.'), 1);
			switch (m_scaleFactor) {
			case 0:
				tmp.remove (0, 1);
				break;
			case 1:
				break;
			default:
				tmp.rightJustified ((char) 0, tmp.size () + m_scaleFactor - 1);
			}
			emit valueChanged (i, tmp);
		}
	}
}
