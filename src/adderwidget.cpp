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

#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

#include "adderwidget.h"

AdderWidget::AdderWidget(QWidget *parent)
	:QWidget(parent)
{
	label = new QLabel(this);
	label->setFrameShape(QFrame::Box);
	label->setAlignment(Qt::AlignTop);


	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(label);
	setLayout(mainLayout);
}

void AdderWidget::updateText()
{
	QStringList text;
	text << "<p align=center><span style=\" font-weight:600; text-decoration: underline;\">" + m_caption + "</span></p>";
	text << "<p> a + b </p>";

	label->setText(text.join("\n"));
}
