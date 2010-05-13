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

#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

class QLabel;
class QAction;

#include <QtGui/QWidget>

class OutputWidget : public QWidget {
	Q_OBJECT

private:
	QByteArray m_values[6];
	QList<QLabel*> labels;
	QString m_captions [6];
	int m_scaleFactor;

public:
	OutputWidget (QWidget *parent = 0);
	virtual ~OutputWidget ()
	{}

	void setInputCaptions (const QStringList& captions); 

	QByteArray saveState () const;
	void restoreState (QByteArray state);

private:
	void retranslateStrings ();

protected:
	void paintEvent (QPaintEvent *ev);
	bool eventFilter (QObject *o, QEvent *ev);
	bool event (QEvent *ev);

private Q_SLOTS:
	void updateLabelsText ();
	void setValue (int index, const QByteArray& value);
	void setScaledFactor (int scaledFactor);
};

#endif //OUTPUTWIDGET_H
