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
#include <QtCore/QSettings>

#include <QtGui/QtEvents>
#include <QtGui/QVBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QApplication>
#include <QtGui/QScrollArea>
#include <QtGui/QStyle>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QToolBar>

#include "mainwindow.h"
#include "microcircuitwidget.h"
#include "aboutdialog.h"

MainWindow::MainWindow (QWidget* parent, Qt::WFlags f)
		: QMainWindow (parent, f)
{
	resize (800, 600);

	QScrollArea *area = new QScrollArea (this);
	area->setWidgetResizable (true);
	area->setFrameShape (QFrame::NoFrame);
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
	actionAddMicrocircuit->setIcon (QIcon(":/share/images/add.png"));
	connect (actionAddMicrocircuit, SIGNAL (triggered ()), this, SLOT (addMicrocircuit ()));

	actionStart = new QAction (this);
	actionStart->setIcon (style ()->standardIcon (QStyle::SP_MediaPlay));
	connect (actionStart, SIGNAL (triggered ()), this, SLOT (start ()));

	actionOpen = new QAction (this);
	actionOpen->setShortcut (QKeySequence::Open);
	actionOpen->setIcon (style ()->standardIcon (QStyle::SP_DialogOpenButton));
	connect (actionOpen, SIGNAL (triggered ()), this, SLOT (open ()));

	actionSave = new QAction (this);
	actionSave->setShortcut (QKeySequence::Save);
	actionSave->setIcon (style ()->standardIcon (QStyle::SP_DialogSaveButton));
	connect (actionSave, SIGNAL (triggered ()), this, SLOT (save ()));

	actionExit = new QAction (this);
	actionExit->setShortcut (Qt::ALT + Qt::Key_X);
	actionExit->setIcon (QIcon(":/share/images/exit.png"));
	connect (actionExit, SIGNAL (triggered ()), this, SLOT (close ()));

	actionAbout = new QAction(this);
	actionAbout->setIcon(QIcon(":/share/images/about.png"));
	connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

	actionAboutQt = new QAction(this);
	actionAboutQt->setIcon(QIcon(":/share/images/aboutQt.png"));
	connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	QMenuBar *mainMenu = new QMenuBar (this);
	setMenuBar (mainMenu);

	fileMenu = new QMenu (this);
	fileMenu->addAction (actionOpen);
	fileMenu->addAction (actionSave);
	fileMenu->addSeparator ();
	fileMenu->addAction (actionExit);
	mainMenu->addMenu (fileMenu);

	operationsMenu = new QMenu (this);
	operationsMenu->addAction (actionAddMicrocircuit);
	operationsMenu->addAction (actionStart);
	mainMenu->addMenu (operationsMenu);

	helpMenu = new QMenu(this);
	helpMenu->addAction(actionAbout);
	helpMenu->addAction(actionAboutQt);

	mainMenu->addMenu(helpMenu);


	toolBar = new QToolBar (this);
	toolBar->setObjectName ("TOOL_BAR");
	toolBar->addAction (actionAddMicrocircuit);
	toolBar->addAction (actionStart);
	toolBar->addSeparator ();
	toolBar->addAction (actionOpen);
	toolBar->addAction (actionSave);
	toolBar->addSeparator ();
	toolBar->addAction (actionAbout);
	toolBar->addAction (actionAboutQt);
	toolBar->addSeparator ();
	toolBar->addAction (actionExit);
	addToolBar (toolBar);

	retranslateStrings ();
}

MainWindow::~MainWindow ()
{

}

void MainWindow::retranslateStrings ()
{
	fileMenu->setTitle (tr ("File"));
	operationsMenu->setTitle (tr ("Operations"));
	helpMenu->setTitle(tr("&Help"));

	toolBar->setWindowTitle (tr ("Main toolbar"));

	actionAddMicrocircuit->setText (tr ("Add microcircuit"));
	actionStart->setText (tr ("Start"));
	actionOpen->setText (tr ("Open"));
	actionSave->setText (tr ("Save"));
	actionExit->setText (tr ("Exit"));
	actionAbout->setText(tr("About..."));
	actionAboutQt->setText(tr("About Qt"));
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

void MainWindow::start ()
{
	QList <MicrocircuitWidget*> l = findChildren<MicrocircuitWidget*> ();

	foreach (MicrocircuitWidget* w, l) {
		if (!w->isValid ()) {
			QMessageBox::critical (this, "", tr ("Microcircuit is not valid"));
			return;
		}
	}

	foreach (MicrocircuitWidget* w, l) {
		w->start ();
	}

}

void MainWindow::saveState (const QString& fileName)
{
	QSettings settings (fileName, QSettings::IniFormat);

	settings.remove ("States");

	settings.beginWriteArray ("States");

	int i = 0;
	foreach (MicrocircuitWidget* w, findChildren<MicrocircuitWidget*> ()) {
		settings.setArrayIndex (i++);
		settings.setValue ("State", w->saveState ());
	}
	settings.endArray();
}

void MainWindow::restoreState (const QString& fileName)
{
	qDeleteAll (findChildren<MicrocircuitWidget*> ());
	
	QSettings settings (fileName, QSettings::IniFormat);

	const int size = settings.beginReadArray("States");

	QVBoxLayout *layout = qobject_cast<QVBoxLayout*> (centralWidget->layout ());
	Q_ASSERT (layout != 0);

	for (int i = 0; i < size; i++) {
		settings.setArrayIndex (i);
		MicrocircuitWidget *w = new MicrocircuitWidget (this);
		layout->insertWidget ((findChildren<MicrocircuitWidget*> ()).size () - 1, w);

		QByteArray state = settings.value ("State").toByteArray ();
		w->restoreState (state);
	}
	settings.endArray();
}

void MainWindow::open ()
{
	const QString& fileName = QFileDialog::getOpenFileName (this, 
															tr ("Open file"),
															"",
															tr ("POSCLabComplex files (*.plc)"));
	if (!fileName.isEmpty ()) {
		restoreState (fileName);
	}
}

void MainWindow::save ()
{
	const QString& fileName = QFileDialog::getSaveFileName (this, 
															tr ("Save file"),
															"",
															tr ("POSCLabComplex files (*.plc)"));
	if (!fileName.isEmpty ()) {
		saveState (fileName);
	}
}

void MainWindow::about()
{
	AboutDialog d (this);

	d.setAuthor(tr("PanteR"));
	d.setMail("panter.dsd@gmail.com");
	d.setPhone("89094119675");
	d.setLicense("GNU GPL v3");

	{
		QFile file(":/LICENSE.GPL3");
		if (file.open(QFile::ReadOnly)) {
			d.setLicenseText(QString(file.readAll()));
			file.close();
		}
	}

	d.addThanks("Bespalov D.A.", "", tr ("Theory"));
	d.exec();
}
