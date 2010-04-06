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

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QtCore/QByteArray>

class Operations {

//	enum OperationType {
//
//	};

private:
	QByteArray m_firstValue;
	QByteArray m_secondValue;

public:
	Operations()
	{}
	virtual ~Operations()
	{}

	QByteArray firstValue()
	{ return m_firstValue; }
	void setFirstValue(const QByteArray& value);

	QByteArray secondValue()
	{ return m_secondValue; }
	void setsecondValue(const QByteArray& value);

	static QByteArray decToBin (double dec, int decimals);

};

#endif //OPERATIONS_H
