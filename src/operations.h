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
	Operations ()
	{}
	virtual ~Operations ()
	{}

	QByteArray firstValue ()
	{ return m_firstValue; }
	void setFirstValue (const QByteArray& value);

	QByteArray secondValue ()
	{ return m_secondValue; }
	void setsecondValue (const QByteArray& value);

	static QByteArray decToBin (double dec, int decimals);
	static QByteArray dizssFromChanels (const QByteArray& positiveChanel, const QByteArray& negativeChanel);
	static void dizssToChanels (const QByteArray& dizss, QByteArray *positiveChanel, QByteArray *negativeChanel);
	static QString binToString (const QByteArray& bin);
	static QString binToHtmlString (const QByteArray& bin);
	static QByteArray stringToBin (const QString& string);
	static QByteArray normalizeBin (const QByteArray& bin);
	static QByteArray add (const QByteArray& first, const QByteArray& second, QString *html = 0);
	static QByteArray mul (const QByteArray& first, const QByteArray& second, QString *html = 0);
	static QByteArray invert (const QByteArray& value);
	static QByteArray scaleIn (const QByteArray& value, int scaleFactor);
	static QByteArray scaleOut (const QByteArray& value, int scaleFactor);
	static int compare (const QByteArray& first, const QByteArray& second);
};

#endif //OPERATIONS_H
