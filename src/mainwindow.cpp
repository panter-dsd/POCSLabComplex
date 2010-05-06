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

#include <QtGui/QtEvents>
#include <QtGui/QVBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QApplication>
#include <QtGui/QScrollArea>

#include "mainwindow.h"
#include "microcircuitwidget.h"

MainWindow::MainWindow (QWidget* parent, Qt::WFlags f)
		: QMainWindow (parent, f)
{
	resize (800, 600);

	QScrollArea *area = new QScrollArea (this);
	area->setWidgetResizable (true);
	setCentralWidget (area);

	centralWidget = new QWidget (this);
	area->setWidget (centralWidget);
	//setCentralWidget (centralWidget);

	//Set font for centralWidget
	QFont m_font (centralWidget->font ());
	m_font.setFamily ("Courier");
	m_font.setPointSize (8);
	centralWidget->setFont (m_font);

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->addSpacerItem (new QSpacerItem (0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding));
	centralWidget->setLayout (mainLayout);

	actionAddMicrocircuit = new QAction (this);
	connect (actionAddMicrocircuit, SIGNAL (triggered ()), this, SLOT (addMicrocircuit ()));

	QMenuBar *mainMenu = new QMenuBar (this);
	setMenuBar (mainMenu);

	fileMenu = new QMenu (this);
	fileMenu->addAction (actionAddMicrocircuit);
	mainMenu->addMenu (fileMenu);

	retranslateStrings ();
}

MainWindow::~MainWindow ()
{

}

void MainWindow::retranslateStrings ()
{
	fileMenu->setTitle (tr ("File"));

	actionAddMicrocircuit->setText (tr ("Add microprocessor"));
}

bool MainWindow::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QMainWindow::event (ev);
}

void MainWindow::addMicrocircuit ()
{
	QVBoxLayout *layout = qobject_cast<QVBoxLayout*> (centralWidget->layout ());

	Q_ASSERT (layout != 0);

	layout->insertWidget ((findChildren<MicrocircuitWidget*> ()).size () - 1, new MicrocircuitWidget (this));
}
