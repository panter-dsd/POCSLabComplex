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

#ifndef ABSTRACTCOMPUTERUNIT_H
#define ABSTRACTCOMPUTERUNIT_H

#include <QtCore/QByteArray>

class AbstractComputerUnit {

protected:
	QByteArray m_value;
	QByteArray m_a;
	QByteArray m_b;

public:
	AbstractComputerUnit();
	virtual ~AbstractComputerUnit()
	{}

	QByteArray value()
	{ return m_value;}

	QByteArray aValue()
	{ return m_a;}
	void setAValue(const QByteArray& a)
	{ m_a = a;}

	QByteArray bValue()
	{ return m_b;}
	void setBValue(const QByteArray& b)
	{ m_b = b;}

	QByteArray add();

private:
	void prepareNumbers(QByteArray *a, QByteArray *b);
};

#endif //ABSTRACTCOMPUTERUNIT_H
