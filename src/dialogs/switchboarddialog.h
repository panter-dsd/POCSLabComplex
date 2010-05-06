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

#ifndef SWITCHBOARDDIALOG_H
#define SWITCHBOARDDIALOG_H

class QComboBox;
class QListWidget;
class QGroupBox;
class QPushButton;
class QLabel;

#include <QtCore/QMap>

#include <QtGui/QDialog>

class SwitchboardDialog : public QDialog {
	Q_OBJECT

private:
	QStringList m_inputCaptions;
	QStringList m_outputCaptions;
	QMap <int, int> m_connections;

	QGroupBox *group;
	QLabel *inputLabel;
	QComboBox *inputBox;
	QLabel *outputLabel;
	QComboBox *outputBox;
	QPushButton *addButton;
	QPushButton *removeButton;
	QListWidget *switchesList;
	
public:
	SwitchboardDialog (QWidget *parent = 0);
	virtual ~SwitchboardDialog ()
	{}

	void setInputCaptions (const QStringList& captions);
	void setOutputCaptions (const QStringList& captions);

	QMap <int, int> connections () const
	{ return m_connections; }
	void setConnections (QMap <int, int> connections);

private:
	void retranslateStrings ();
	void updateBoxes ();
	void updateSwitchesList ();

protected:
	bool event (QEvent *ev);

private Q_SLOTS:
	void addSwitch ();
	void removeSwitch ();
};


#endif //SWITCHBOARDDIALOG_H
