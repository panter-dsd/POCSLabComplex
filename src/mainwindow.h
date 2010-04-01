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

class MicroprocessorWidget;
class QAction;
class QMenu;
class QVBoxLayout;

#include <QtGui/QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QList<MicroprocessorWidget*> microprocessorsList;
	QVBoxLayout *microprocessorsLayout;

	QMenu *fileMenu;

	QAction *actionAddMicroprocessor;

public:
	MainWindow(QWidget* parent = 0, Qt::WFlags f = 0);
	~MainWindow();

private:
	void retranslateStrings();

protected:
	bool event(QEvent *ev);

private Q_SLOTS:
	void addMicroprocessor();
};

#endif // MAINWINDOW_H
