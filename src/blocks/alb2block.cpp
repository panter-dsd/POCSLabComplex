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

#include "alb2block.h"
#include "operationdialog.h"
#include "operations.h"

Alb2Block::Alb2Block (const QString& caption, QWidget *parent)
	: AbstractBlock (caption, parent)
{
	operations.insert (0, "a + b");
	operations.insert (1, "a - b");
	operations.insert (2, "0 + b");
	operations.insert (3, "a + (b > 0/0)");
	operations.insert (4, " (a + b)/2");
	operations.insert (5, " (a - b)/2");
	operations.insert (6, " (0 + b)/2");
	operations.insert (7, "a - (b > 0/0)");

	moduleOperations.insert (0, "|a + b|");
	moduleOperations.insert (1, "|a - b|");
	moduleOperations.insert (2, "|a + 0|");
	moduleOperations.insert (4, "| (a + b)/2|");
	moduleOperations.insert (5, "| (a - b)/2|");
	moduleOperations.insert (6, "| (a + 0)/2|");
}

void Alb2Block::chooseOperation ()
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

bool Alb2Block::calculate ()
{
	if (!isValid ()) {
		return false;
	}

	m_report.clear ();

	switch (m_operation) {
	case 0:
		m_calculatedValue = Operations::add (m_firstValue, m_secondValue, &m_report);
		break;
	case 1:
		m_calculatedValue = Operations::add (m_firstValue, Operations::invert(m_secondValue), &m_report);
		break;
	case 2:
		m_calculatedValue = Operations::add (QByteArray (), m_secondValue, &m_report);
		break;
	case 3:
		break;
	case 4:
		m_calculatedValue = Operations::scaleIn (Operations::add (m_firstValue, m_secondValue, &m_report), 1);
		break;
	case 5:
		m_calculatedValue = Operations::scaleIn (Operations::add (m_firstValue, Operations::invert(m_secondValue), &m_report), 1);
		break;
	case 6:
		m_calculatedValue = Operations::scaleIn (Operations::add (QByteArray (), m_secondValue, &m_report), 1);
		break;
	case 7:
		break;
	}

	updateToolTip ();
	return true;
}
