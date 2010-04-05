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

#include <QtGui/QHBoxLayout>

#include "microcircuitwidget.h"
#include "inoutwidget.h"
#include "switchboardwidget.h"
#include "microprocessorwidget.h"

MicrocircuitWidget::MicrocircuitWidget (QWidget *parent)
	: QWidget (parent)
{
	inputInOut = new InOutWidget (this);

	inputSwitchboard = new SwitchboardWidget (this);

	microprocessor = new MicroprocessorWidget (this);

	outputSwitchboard = new SwitchboardWidget (this);

	outputInOut = new InOutWidget (this);

	QHBoxLayout *mainLayout = new QHBoxLayout ();
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(inputInOut);
	mainLayout->addWidget(inputSwitchboard);
	mainLayout->addWidget(microprocessor);
	mainLayout->addWidget(outputSwitchboard);
	mainLayout->addWidget(outputInOut);
	setLayout (mainLayout);
}
