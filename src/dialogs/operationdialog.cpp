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

#include <QtGui/QGroupBox>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QDialogButtonBox>

#include "operationdialog.h"

OperationDialog::OperationDialog (QMap<char, QString> operations, QWidget *parent)
	:QDialog (parent)
{
	groupBox = new QGroupBox (this);

	QVBoxLayout *layout = new QVBoxLayout ();

	QRadioButton *radioButton;

	QMapIterator<char, QString> it (operations);

	while (it.hasNext ()) {
		it.next ();

		radioButton = new QRadioButton (it.value (), this);
		radioButton->setObjectName (QString::number (it.key ()));

		layout->addWidget (radioButton);
	}

	groupBox->setLayout (layout);

	QDialogButtonBox *buttons = new QDialogButtonBox (QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
													 Qt::Horizontal,
													 this);
	connect (buttons, SIGNAL (accepted ()), this, SLOT (accept ()));
	connect (buttons, SIGNAL (rejected ()), this, SLOT (reject ()));

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->addWidget (groupBox);
	mainLayout->addWidget (buttons);
	setLayout (mainLayout);
}

int OperationDialog::operation ()
{
	foreach (QRadioButton *rb, findChildren<QRadioButton*> ())
		if (rb->isChecked ())
			return rb->objectName ().toInt ();

	return -1;
}

void OperationDialog::setOperation (int operation)
{
	foreach (QRadioButton *rb, findChildren<QRadioButton*> ()) {
		if (rb->objectName ().toInt () == operation) {
			rb->setChecked (true);
			break;
		}
	}
}
