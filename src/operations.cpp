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

#include <QtCore/QDebug>

#include "operations.h"

void Operations::setFirstValue(const QByteArray& value)
{
	m_firstValue = value;
}

void Operations::setsecondValue(const QByteArray& value)
{
	m_secondValue = value;
}

QByteArray Operations::decToBin (double dec, int decimals)
{
	QByteArray value;

	for (int i = 0; i < decimals && dec != 0; i++) {
		dec *= 2;

		if (dec >= 1) {
			value.append('1');
			dec -= 1;
		} else {
			value.append('0');
		}
	}
	return value;
}
