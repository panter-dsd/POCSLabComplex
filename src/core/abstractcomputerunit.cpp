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

#include "abstractcomputerunit.h"

AbstractComputerUnit::AbstractComputerUnit()
{

}

void AbstractComputerUnit::prepareNumbers(QByteArray *a, QByteArray *b)
{
	int indexA = a->indexOf('.');
	int indexB = b->indexOf('.');

	if ((indexA == indexB) && (a->size() != b->size())) {
		while (a->size() < b->size())
			a->append((char)0);
		while (a->size() > b->size())
			b->append((char)0);
	}

}

QByteArray AbstractComputerUnit::add()
{
	QByteArray a(m_a);
	QByteArray b(m_b);
	prepareNumbers(&a, &b);
}
