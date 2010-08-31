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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MicrocircuitWidget;
class QAction;
class QMenu;
class QWidget;
class QToolBar;

#include <QtGui/QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QWidget *centralWidget;

	QMenu *fileMenu;
	QMenu *operationsMenu;
	QMenu *helpMenu;
 
	QAction *actionAddMicrocircuit;
	QAction *actionStart;
	QAction *actionOpen;
	QAction *actionSave;
	QAction *actionExit;

	QAction *actionAbout;
	QAction *actionAboutQt;

	QToolBar *toolBar;

public:
	MainWindow (QWidget* parent = 0, Qt::WFlags f = 0);
	~MainWindow ();

private:
	void retranslateStrings ();
	void saveState (const QString& fileName);
	void restoreState (const QString& fileName);
	void loadSettings();
	void saveSettings(); 

protected:
	bool event (QEvent *ev);

private Q_SLOTS:
	void addMicrocircuit ();
	void start ();
	void open ();
	void save ();
	void about();
};

#endif // MAINWINDOW_H
