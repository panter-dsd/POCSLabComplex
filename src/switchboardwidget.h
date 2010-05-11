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

#ifndef SWITCHBOARDWIDGET_H
#define SWITCHBOARDWIDGET_H

class QAction;

#include <QtCore/QMap>

#include <QtGui/QWidget>

class SwitchboardWidget : public QWidget {
	Q_OBJECT

private:
	QPoint inputPoints [6];
	QPoint outputPoints [6];
	QStringList m_inputCaptions;
	QStringList m_outputCaptions;
	QMap <int, int> m_connections;
	QByteArray m_inputValues [6];

	QAction *actionSetConnections;

public:
	SwitchboardWidget (QWidget *parent = 0);
	virtual ~SwitchboardWidget ()
	{}

	void setInputCaptions (const QStringList& captions);
	void setOutputCaptions (const QStringList& captions);

	void setInputValues (QByteArray values [6]) 
	{
		for (int i = 0; i < 6; i++) {
			m_inputValues [i] = values [i];
		}
	}

	QByteArray outputValue (int index) const;

	bool isValid () const;

	QByteArray saveState () const;
	void restoreState (QByteArray state);

private:
	void retranslateStrings ();

protected:
	void paintEvent (QPaintEvent *ev);
	bool event (QEvent *ev);

private Q_SLOTS:
	void setConnections ();
	void setValue (int index, const QByteArray& value);

Q_SIGNALS:
	void valueChanged (int index, const QByteArray& value);
};

#endif //SWITCHBOARDWIDGET_H
