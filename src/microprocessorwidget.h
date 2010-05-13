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

#ifndef MICROPROCESSORWIDGET_H
#define MICROPROCESSORWIDGET_H

class QPainter;
class QAction;
class AbstractBlock;
class Alb1Block;
class Alb2Block;
class Alb3Block;
class Mb1Block;
class Mb2Block;

#include <QtGui/QWidget>

class MicroprocessorWidget : public QWidget
{
	Q_OBJECT

public:
	enum Inputs {
		Input_0 = 0,
		Input_1,
		Input_2,
		Input_3,
		Input_4,
		Input_5,
		CountInputs
	};
	enum Outputs {
		Output_0 = 0,
		Output_1,
		Output_2,
		Output_3,
		Output_4,
		Output_5,
		CountOutputs
	};


private:
	Alb1Block *alb1;
	Alb2Block *alb2;
	Alb3Block *alb3;
	Mb1Block *mb1;
	Mb2Block *mb2;

	QAction *actionChooseScheme;
	QAction *actionSetModule;

	QRect m_workRect;
	QRect m_rect;
	qint8 m_scheme;
	quint16 m_adjustingWord;
	QPoint inputPoints [CountInputs];
	QPoint outputPoints [CountOutputs];
	QString m_inputCaptions [CountInputs];
	QString m_outputCaptions [CountOutputs];
	QByteArray inputValues [CountInputs];
	QByteArray outputValues [CountOutputs];
	bool m_isModule;

	QString m_name;

public:
	MicroprocessorWidget (QWidget *parent);
	virtual ~MicroprocessorWidget ()
	{}

	quint16 adjustingWord () const
	{ return m_adjustingWord; }
	void setAdjustingWord (quint16 m_adjustingWord);

	QString name ()
	{ return m_name; }

	int inputsCount () const;
	int outputsCount () const;

	QStringList inputCaptions () const;
	QStringList outputCaptions () const;

	bool isValid () const;

	QByteArray saveState () const;
	void restoreState (QByteArray state);

	bool calculate ();

protected:
	void paintEvent (QPaintEvent *ev);
	void resizeEvent (QResizeEvent *ev);
	void updateWidgets ();

private:
	void paint_0 (QPaintEvent *ev, QPainter *painter);
	void resize_0 ();
	bool calculate_0 ();
	void paint_1 (QPaintEvent *ev, QPainter *painter);
	void resize_1 ();
	bool calculate_1 ();
	void paint_2 (QPaintEvent *ev, QPainter *painter);
	void resize_2 ();
	bool calculate_2 ();
	void paint_4 (QPaintEvent *ev, QPainter *painter);
	void resize_4 ();
	bool calculate_4 ();
	void paint_5 (QPaintEvent *ev, QPainter *painter);
	void resize_5 ();
	bool calculate_5 ();
	void paint_6 (QPaintEvent *ev, QPainter *painter);
	void resize_6 ();
	bool calculate_6 ();
	void retranslateStrings ();
	void setCaptions ();
	void clearValues ();

protected:
	bool event (QEvent *ev);

private Q_SLOTS:
	void chooseScheme ();
	void updateAdjustingWorld ();
	void setValue (int index, const QByteArray& value);
	void setModule (bool isModule);

Q_SIGNALS:
	void nameChanged (const QString& name);
	void schemeChanged ();
	void valueChanged (int index, const QByteArray& value);
};

#endif //MICROPROCESSORWIDGET_H
