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

void Operations::setFirstValue (const QByteArray& value)
{
	m_firstValue = value;
}

void Operations::setsecondValue (const QByteArray& value)
{
	m_secondValue = value;
}

QByteArray Operations::decToBin (double dec, int decimals)
{
	QByteArray value;

	for (int i = 0; i < decimals && dec != 0; i++) {
		dec *= 2;

		if (dec >= 1) {
			value.append ('1');
			dec -= 1;
		} else {
			value.append ('0');
		}
	}
	return value;
}

QByteArray Operations::dizssFromChanels (const QByteArray& positiveChanel, const QByteArray& negativeChanel)
{
	QByteArray positive (positiveChanel);
	QByteArray negative (negativeChanel);
	for (int i = 0; i < positive.size (); i++) {
		if (positive [i] != (char) 0 && positive [i] != (char) 1) {
			positive.remove (i--, 1);
		}
	}
	for (int i = 0; i < negative.size (); i++) {
		if (negative [i] != (char) 0 && negative [i] != (char) 1) {
			negative.remove (i--, 1);
		}
	}

	QByteArray value;

	{
		const int size = positive.size () > negative.size () ? positive.size () : negative.size ();
		value.fill ((char) 0, size);
	}

	for (int i = 0, size = positive.size (); i < size; i++) {
		if (positive [i] == (char) 0 || positive [i] == (char) 1) {
			value [i] = positive [i];
		}
	}

	for (int i = 0, size = negative.size (); i < size; i++) {
		if (negative [i] == (char) 1) {
			if (value [i] == (char) 1)
				return QByteArray ();
			else
				value [i] = (char) -1;
		} else {
			if (negative [i] != (char) 0) {
				value [i] = negative [i];
			}
		}
	}
	value.insert (1, '.');
	return value.size () > 2 ? value : QByteArray ();
}

QString Operations::binToString (const QByteArray& bin)
{
	QString out;

	for (int i = 0, size = bin.size (); i < size; i++) {
		switch (bin [i]) {
			case -1: out += "-1"; break;
			case 0: out += "0"; break;
			case 1: out += "1"; break;
			default: out += bin [i];
		}
	}
	return out;
}

QByteArray Operations::stringToBin (const QString& string)
{
	QByteArray out;

	bool isMinus = false;
	for (int i = 0, size = string.size (); i < size; i++) {
		if (string [i] == '-') {
			isMinus = true;
			continue;
		}

		if (isMinus && string [i] != '1')
			return QByteArray ();

		if (string [i] == '0') {
			out += (char) 0;
		} else {
			if (string [i] == '1') {
				out += isMinus ? (char) -1 : (char) 1;
			} else {
				out += string [i];
			}
		}
		isMinus = false;
	}
	return out;
}

void Operations::dizssToChanels (const QByteArray& dizss, QByteArray *positiveChanel, QByteArray *negativeChanel)
{
	positiveChanel->clear ();
	negativeChanel->clear ();

	for (int i = 0, size = dizss.size (); i < size; i++) {
		switch (dizss [i]) {
		case (char) 1 : 
			positiveChanel->append ((char) 1);
			negativeChanel->append ((char) 0);
			break;
		case (char) -1 : 
			positiveChanel->append ((char) 0);
			negativeChanel->append ((char) -1);
			break;
		default:
			positiveChanel->append (dizss [i]);
			negativeChanel->append (dizss [i]);

		}
	}
}

QByteArray Operations::normalizeBin (const QByteArray& bin)
{
	QByteArray tmp (bin);

	while (!tmp.isEmpty () && tmp [tmp.size () - 1] == (char) 0) {
		tmp.remove (tmp.size () - 1, 1);
	}
	if (tmp.size () < 3) {
		tmp.clear ();
	}

	return tmp;
}
