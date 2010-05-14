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

#include "mb1block.h"
#include "operationdialog.h"
#include "operations.h"

Mb1Block::Mb1Block (const QString& caption, QWidget *parent)
	: AbstractBlock (caption, parent)
{
	operations.insert (0, "a * b");
	operations.insert (1, " (a + b)/2");
	operations.insert (2, "a");
	operations.insert (3, "a - b");
}

void Mb1Block::chooseOperation ()
{
	const QMap<char, QString> &m = m_isModule ? moduleOperations : operations;

	OperationDialog d (m, this);

	d.setOperation (m_operation);

	if (d.exec ()) {
		m_operation = d.operation ();
		updateToolTip ();
		emit operationChanged (m_operation);
	}
}

bool Mb1Block::calculate ()
{
	if (!isValid ()) {
		return false;
	}

	m_report.clear ();

	switch (m_operation) {
	case 0:
		m_calculatedValue = Operations::mul (m_firstValue, m_secondValue, &m_report);
		break;
	case 1:
		m_calculatedValue = Operations::scaleIn (Operations::add (m_firstValue, m_secondValue, &m_report), 1);
		break;
	case 2:
		m_calculatedValue = m_firstValue;
		break;
	case 3:
		m_calculatedValue = Operations::add (m_firstValue, Operations::invert(m_secondValue), &m_report);
		break;
	}

	updateToolTip ();
	return true;
}
