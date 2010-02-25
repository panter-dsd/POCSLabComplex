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
* along with Panther Commander; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA 02110-1301 USA
*-------------------------------------------------------------------
* Project:POCSLabComplex
* Author:PanteR
* Contact:panter.dsd@gmail.com
*******************************************************************/

#include <QtCore/QDebug>

#include <QtGui/QInputDialog>

#include "mb2block.h"
#include "operationdialog.h"

Mb2Block::Mb2Block(const QString& caption, QWidget *parent)
	: AbstractBlock(caption, parent)
{
	operations.insert(0, "a * b");
	operations.insert(1, "(a + b)/2");
	operations.insert(2, "a");
	operations.insert(3, "a - b");
}

void Mb2Block::chooseOperation()
{
	const QMap<int, QString> &m = m_isModule ? moduleOperations : operations;

	OperationDialog d(m, this);

	d.setOperation(m_operation);

	if (d.exec()) {
		m_operation = d.operation();
		updateToolTip();
		emit operationChanged(m_operation);
	}
}

void Mb2Block::updateToolTip()
{
	QString m_toolTip = "<h2 align=center><u>" + m_caption + "</u></h2>";

	if (m_operation >= 0) {
		m_toolTip += "<p><b>";
		m_toolTip += tr("Current operation");
		m_toolTip += "</b>: ";
		if (m_isModule)
			m_toolTip += moduleOperations.value(m_operation);
		else
			m_toolTip += operations.value(m_operation);
		m_toolTip += "</p>";
	}

	setToolTip(m_toolTip);
}
