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

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QtEvents>
#include <QtGui/QToolButton>
#include <QtGui/QStyle>

#include "microcircuitwidget.h"
#include "inputwidget.h"
#include "outputwidget.h"
#include "switchboardwidget.h"
#include "microprocessorwidget.h"

MicrocircuitWidget::MicrocircuitWidget (QWidget *parent)
	: QWidget (parent)
{
	inputLabel = new QLabel (this);
	inputLabel->setAlignment (Qt::AlignHCenter);

	inputSwitchboardLabel = new QLabel (this);
	inputSwitchboardLabel->setAlignment (Qt::AlignHCenter);

	microprocessorLabel = new QLabel (this);
	microprocessorLabel->setAlignment (Qt::AlignHCenter);

	outputLabel = new QLabel (this);
	outputLabel->setAlignment (Qt::AlignHCenter);

	inputWidget = new InputWidget (this);

	inputSwitchboard = new SwitchboardWidget (this);
	connect (inputWidget, SIGNAL (valueChanged (int, QByteArray)), inputSwitchboard, SLOT (setValue (int, QByteArray)));

	microprocessor = new MicroprocessorWidget (this);
	microprocessorLabel->setText (microprocessor->name ());
	connect (microprocessor, SIGNAL (nameChanged (QString)), this, SLOT (microprocessorNameChanged (QString)));
	connect (microprocessor, SIGNAL (schemeChanged ()), this, SLOT (microprocessorSchemeChanged ()));
	connect (inputSwitchboard, SIGNAL (valueChanged (int, QByteArray)), microprocessor, SLOT (setValue (int, QByteArray)));

	outputWidget = new OutputWidget (this);
	connect (inputWidget, SIGNAL (scaledFactorChanged (int)), outputWidget, SLOT (setScaledFactor (int)));
	connect (microprocessor, SIGNAL (valueChanged (int, QByteArray)), outputWidget, SLOT (setValue (int, QByteArray)));

	closeButton = new QToolButton (this);
	closeButton->setIcon (style ()->standardIcon (QStyle::SP_TitleBarCloseButton));
	closeButton->setAutoRaise (true);
	connect (closeButton, SIGNAL (clicked ()), this, SLOT (deleteLater ()));

	QGridLayout *mainLayout = new QGridLayout ();
	mainLayout->setContentsMargins (0, 0, 0, 0);
	mainLayout->setSpacing (0);
	mainLayout->addWidget (inputLabel, 0, 0);
	mainLayout->addWidget (inputSwitchboardLabel, 0, 1);
	mainLayout->addWidget (microprocessorLabel, 0, 2);
	mainLayout->addWidget (outputLabel, 0, 3);
	mainLayout->addWidget (closeButton, 0, 4);

	mainLayout->addWidget (inputWidget, 1, 0);
	mainLayout->addWidget (inputSwitchboard, 1, 1);
	mainLayout->addWidget (microprocessor, 1, 2);
	mainLayout->addWidget (outputWidget, 1, 3);
	setLayout (mainLayout);

	retranslateStrings ();
}

void MicrocircuitWidget::retranslateStrings ()
{
	inputLabel->setText (tr ("Input"));
	inputSwitchboardLabel->setText (tr ("Switchboard"));
	outputLabel->setText (tr ("Output"));
	closeButton->setText (tr ("Close"));
	closeButton->setToolTip (tr ("Close"));
}

bool MicrocircuitWidget::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QWidget::event (ev);
}

void MicrocircuitWidget::microprocessorNameChanged (const QString& name)
{
	microprocessorLabel->setText (name);
}

void MicrocircuitWidget::microprocessorSchemeChanged ()
{
	inputWidget->setCount (microprocessor->inputsCount ());
	inputSwitchboard->setInputCaptions(inputWidget->outputCaptions ());
	inputSwitchboard->setOutputCaptions (microprocessor->inputCaptions ());
	outputWidget->setInputCaptions (microprocessor->outputCaptions ());
}

bool MicrocircuitWidget::isValid () const
{
	return inputWidget->isValid () && inputSwitchboard->isValid () && microprocessor->isValid ();
}

void MicrocircuitWidget::start ()
{
	microprocessor->calculate ();
}

QByteArray MicrocircuitWidget::saveState () const
{
	QByteArray state;

	QDataStream stream (&state, QIODevice::WriteOnly);
	stream << microprocessor->saveState ();
	stream << inputWidget->saveState ();
	stream << inputSwitchboard->saveState ();

	return state;
}

void MicrocircuitWidget::restoreState (QByteArray state)
{
	QDataStream stream (&state, QIODevice::ReadOnly);

	QByteArray data;
	stream >> data;
	microprocessor->restoreState (data);
	stream >> data;
	inputWidget->restoreState (data);
	stream >> data;
	inputSwitchboard->restoreState (data);
}
