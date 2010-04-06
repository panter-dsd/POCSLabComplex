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
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QtEvents>
#include <QtGui/QMenu>
#include <QtGui/QAction>

#include "inoutwidget.h"
#include "inputdialog.h"

const int penWidth = 7;

InOutWidget::InOutWidget (Type type, QWidget *parent)
	: QWidget (parent), m_type (type), m_lastIndex (-1), actionChangeValue (0)
{
	setMouseTracking(true);

	if (m_type == In) {
		actionChangeValue = new QAction (this);
		connect (actionChangeValue, SIGNAL(triggered()), this, SLOT(changeValue()));
	}

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->setContentsMargins(penWidth / 2, penWidth / 2, penWidth * 2, penWidth * 2);
	mainLayout->setSpacing(0);

	for (int i = 0; i < 6; i++) {
		QLabel *label = new QLabel (this);
		label->setObjectName(QString::number(i));
		label->setFrameShape(QFrame::Box);
		label->installEventFilter(this);
		label->setContextMenuPolicy(Qt::CustomContextMenu);

		mainLayout->addWidget(label);
		labels.append(label);
	}
	setLayout(mainLayout);

	retranslateStrings();
}

void InOutWidget::retranslateStrings()
{
	if (actionChangeValue)
		actionChangeValue->setText(tr ("Change value"));
}

bool InOutWidget::event(QEvent *ev)
{
	if (ev->type() == QEvent::LanguageChange) {
		retranslateStrings();
	}

	return QWidget::event(ev);
}

void InOutWidget::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::darkGray);
	pen.setWidth(penWidth);
	painter.setPen(pen);

	QRect m_rect(rect().x(), rect().y(), rect().width(), rect().height());

	//Shadow
	painter.drawLine(m_rect.x() + pen.width(), m_rect.y() + m_rect.height() - pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());
	painter.drawLine(m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());

	//Rect
	pen.setBrush(Qt::black);
	painter.setPen(pen);
	m_rect.setWidth(m_rect.width() - pen.width() * 2);
	m_rect.setHeight(m_rect.height() - pen.width() * 2);
	painter.drawRect(m_rect);

	pen.setWidth(1);
	painter.setPen(pen);

	for (int i = 0; i < 6; i++) {
		if (m_type == In) {
			painter.drawLine(labels [i]->x() + labels [i]->width(), labels [i]->y() + labels [i]->height() / 2,
							 width (), labels [i]->y() + labels [i]->height() / 2);
		}
	}
}

bool InOutWidget::eventFilter(QObject *o, QEvent *ev)
{
	if (m_type == In) {
		if (ev->type() == QEvent::MouseButtonDblClick) {
			QLabel *label = qobject_cast<QLabel*> (o);
			actionChangeValue->setParent(label);
			actionChangeValue->trigger();
		}

		if (ev->type() == QEvent::ContextMenu) {
			QContextMenuEvent *contextEvent = static_cast<QContextMenuEvent*> (ev);
			QLabel *label = qobject_cast<QLabel*> (o);
			QMenu menu;
			actionChangeValue->setParent(label);
			menu.addAction(actionChangeValue);
			menu.exec(label->mapToGlobal(contextEvent->pos()));
		}
	}

	return QWidget::eventFilter(0, ev);
}

void InOutWidget::changeValue ()
{
	QAction *action = qobject_cast<QAction*> (sender ());
	if (!action)
		return;

	QLabel *label = qobject_cast<QLabel*> (action->parent());
	if (label) {
		InputDialog d (this);

		if (d.exec()) {
			m_values [label->objectName().toInt()] = d.value();
			label->setText(d.value());
		}
	}
}
