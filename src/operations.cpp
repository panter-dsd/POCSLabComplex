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
#include <QtCore/QStringList>

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

QString Operations::binToHtmlString (const QByteArray& bin)
{
	QString out;

	for (int i = 0, size = bin.size (); i < size; i++) {
		switch (bin [i]) {
			case -1: out += "<span style=\"text-decoration: overline\">1</span>"; break;
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

QByteArray Operations::add (const QByteArray& first, const QByteArray& second, QString *html)
{
	QByteArray a (first);
	QByteArray b (second);
	a = a.rightJustified (b.size (), (char) 0);
	b = b.rightJustified (a.size (), (char) 0);

	QByteArray s1, p1, c0;
	p1.append ((char) 0);
	c0.append ((char) 0);
	c0.append ((char) 0);

	QByteArray s2, p2;
	p2.append ((char) 0);

	QByteArray value;

	//First step

	for (int i = a.size () - 1; i >= 0; i--) {
		switch (a [i]) {
		case (char) -1:
			switch (b [i]) {
			case (char) -1:
				s1.insert (0, (char) 0);
				p1.insert (0, (char) -1);
				c0.insert (0, (char) 0);
				break;
			case (char) 0:
				s1.insert (0, (char) 1);
				p1.insert (0, (char) -1);
				c0.insert (0, (char) 0);
				break;
			case (char) 1:
				s1.insert (0, (char) 0);
				p1.insert (0, (char) 0);
				c0.insert (0, (char) 0);
				break;
			}
			break;
		case (char) 0:
			switch (b [i]) {
			case (char) -1:
				s1.insert (0, (char) 1);
				p1.insert (0, (char) -1);
				c0.insert (0, (char) 0);
				break;
			case (char) 0:
				s1.insert (0, (char) 0);
				p1.insert (0, (char) 0);
				c0.insert (0, (char) 0);
				break;
			case (char) 1:
				s1.insert (0, (char) 1);
				p1.insert (0, (char) 0);
				c0.insert (0, (char) 0);
				break;
			}
			break;
		case (char) 1:
			switch (b [i]) {
			case (char) -1:
				s1.insert (0, (char) 0);
				p1.insert (0, (char) 0);
				c0.insert (0, (char) 0);
				break;
			case (char) 0:
				s1.insert (0, (char) 1);
				p1.insert (0, (char) 0);
				c0.insert (0, (char) 0);
				break;
			case (char) 1:
				s1.insert (0, (char) 0);
				p1.insert (0, (char) -1);
				c0.insert (0, (char) 1);
				break;
			}
			break;
		}
	}

	//Second step

	s1 = s1.rightJustified (p1.size (), (char) 0);

	for (int i = s1.size () - 1; i >= 0; i--) {
		switch (s1 [i]) {
		case (char) -1:
			switch (p1 [i]) {
			case (char) 0:
				s2.insert (0, (char) -1);
				p2.insert (0, (char) 0);
				break;
			case (char) 1:
				s2.insert (0, (char) 0);
				p2.insert (0, (char) 0);
				break;
			}
			break;
		case (char) 0:
			switch (p1 [i]) {
			case (char) -1:
				s2.insert (0, (char) -1);
				p2.insert (0, (char) 0);
				break;
			case (char) 0:
				s2.insert (0, (char) 0);
				p2.insert (0, (char) 0);
				break;
			case (char) 1:
				s2.insert (0, (char) -1);
				p2.insert (0, (char) 1);
				break;
			}
			break;
		case (char) 1:
			switch (p1 [i]) {
			case (char) -1:
				s2.insert (0, (char) 0);
				p2.insert (0, (char) 0);
				break;
			case (char) 0:
				s2.insert (0, (char) -1);
				p2.insert (0, (char) 1);
				break;
			}
			break;
		}
	}

	//Third step

	s2 = s2.rightJustified (c0.size (), (char) 0);
	p2 = p2.rightJustified (c0.size (), (char) 0);

	for (int i = c0.size () - 1; i >= 0; i--) {
		char c = s2 [i] + p2 [i] + c0 [i];

		if (c > 1) {
			c = 0;
		}
		value.insert (0, c);
	}

	if (html) {
		QStringList l;
		l << "<BR><TABLE BORDER=1 BORDERCOLOR=\"#000000\" CELLPADDING=4 CELLSPACING=0>";

		for (int i = 0, size = value.size () + 1; i < size; i++) {
			l << "<COL WIDTH=32*>";
		}

		QString rowStr = "<TR>";
		for (int i = 0, size = value.size () + 1; i < size; i++) {
			rowStr += QString("<TD align=\"center\">-=%1=-</TD>").arg (i);
		}
		rowStr += "</TR>";

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("First value"));

		QString tmpStr = binToString (a);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("Second value"));

		tmpStr = binToString (b);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << "<TR></TR>";

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("S1 &gt;= 0"));

		tmpStr = binToString (s1);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("P1 &lt;= 0"));

		tmpStr = binToString (p1);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << "<TR></TR>";

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("S2 &lt;= 0"));

		tmpStr = binToString (s2);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("P2 &gt;= 0"));

		tmpStr = binToString (p2);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("C0 &gt;= 0"));

		tmpStr = binToString (c0);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << "<TR></TR>";

		l << rowStr;
		l [l.size () - 1].replace (QString ("-=%1=-").arg (value.size ()), QObject::tr ("Result"));

		tmpStr = binToString (value);
		for (int i = value.size () - 1, j = tmpStr.size () - 1; i >= 0; i--, j--) {
			if (j >=1 && tmpStr [j] == '1' && tmpStr [j - 1] == '-') {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j - 1, 2));
				j--;
			} else {
				l [l.size () - 1].replace (QString ("-=%1=-").arg (i), j < 0 ? "<P> </P>" : tmpStr.mid (j, 1));
			}
		}

		l << "</TABLE>";

		for (int i = 0, size = l.size (); i < size; i++) {
			l [i].replace ("-1", "<span style=\"text-decoration: overline\">1</span>");
		}

		*html += l.join ("\n");
	}

	while (value.size () != a.size () && value [0] == (char) 0) {
		value.remove (0, 1);
	}

	return value;
}

QByteArray Operations::mul (const QByteArray& first, const QByteArray& second, QString *html)
{
	QByteArray a (first.size () > second.size () ? first : second); //Lager
	QByteArray b (first.size () <= second.size () ? first : second); //Smaller

	QList <QByteArray> chp;

	for (int i = 0, size = b.size (); i < size; i++) {
		chp.append (a.rightJustified (a.size () + i + 1, (char) 0));

		switch (b [i]) {
		case (char) 0:
			chp [i].fill (char (0));
			break;
		case (char) -1:
			chp [i] = invert (chp [i]);
			break;
		}
	}

	if (html) {
		QStringList l;
		l << "<BR>";

		QByteArray tmp;
		tmp.append ((char) 0);
		tmp.append ('.');
		for (int i = 0, size = chp.size (); i < size; i++) {
			tmp.append (b [i]);
			l << "<P><b>" + QObject::tr ("ChP") + QString ("%1</b>: %2 * %3 = %4").arg (i + 1).arg (binToHtmlString (a)).arg (binToHtmlString (tmp)).arg (binToHtmlString (chp [i])) + "</P>";
			tmp [tmp.size () - 1] = (char) 0;
		}
		*html += l.join ("\n");
	}

	QByteArray result = chp [0];

	for (int i = 1, size = chp.size (); i < size; i++) {
		result = add (result, chp [i], html);
	}
	return result;
}

QByteArray Operations::invert (const QByteArray& value)
{
	QByteArray result (value);

	for (int i = 0, size = result.size (); i < size; i++) {
		result [i] = result [i] * (char) -1;
	}
	
	return result;
}

QByteArray Operations::scaleIn (const QByteArray& value, int scaleFactor)
{
	QByteArray result (value);
	result.remove (result.indexOf ('.'), 1);
	switch (scaleFactor) {
	case 0:
		result.remove (0, 1);
		break;
	case 1:
		break;
	default:
		result = result.rightJustified ((char) 0, result.size () + scaleFactor - 1);
	}

	return result;
}

QByteArray Operations::scaleOut (const QByteArray& value, int scaleFactor)
{
	QByteArray result (value);

	if (scaleFactor == 0) {
		result.insert (1, '.');
	} else {
		result.insert (scaleFactor, '.');
		while (result [1] != '.') {
			result.remove (0, 1);
		}
	}
	
	return result;
}

int Operations::compare (const QByteArray& first, const QByteArray& second)
{
	for (int i = 0, firstSize = first.size (), secondSize = second.size (); i < firstSize && i < secondSize; ++i) {
		if (first [i] != second [i]) {
			return first [i] < second [i] ? -1 : 1;
		}
	}

	if (first.size () != second.size ()) {
		return first.size () < second.size () ? -1 : 1;
	}

	return 0;
}
