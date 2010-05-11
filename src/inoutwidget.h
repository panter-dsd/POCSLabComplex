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

#ifndef INOUTWIDGET_H
#define INOUTWIDGET_H

class QLabel;
class QAction;

#include <QtGui/QWidget>

class InOutWidget : public QWidget {
	Q_OBJECT

public:
	enum Type {
		In = 0,
		Out
	};

private:
	int m_type;
	QByteArray m_values[6];
	QList<QLabel*> labels;
	int m_count;
	QString m_captions [6];

	QAction *actionChangeValue;

public:
	InOutWidget (Type type, QWidget *parent = 0);
	virtual ~InOutWidget ()
	{}

	void setCount (int count);
	void setInputCaptions (const QStringList& captions); 

	QByteArray value (int index) const
	{ return m_values [index]; }

	bool isValid () const;

	QStringList outputCaptions () const;

	QByteArray saveState () const;
	void restoreState (QByteArray state);

private:
	void retranslateStrings ();

protected:
	void paintEvent (QPaintEvent *ev);
	bool eventFilter (QObject *o, QEvent *ev);
	bool event (QEvent *ev);

private Q_SLOTS:
	void changeValue ();
	void updateLabelsText ();
	void setValue (int index, const QByteArray& value);

Q_SIGNALS:
	void valueChanged (int index, const QByteArray& value);
};

#endif //INOUTWIDGET_H
