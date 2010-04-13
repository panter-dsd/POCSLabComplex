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

#include <QtCore/QTextCodec>
#include <QtCore/QSettings>
#include <QtCore/QLocale>
#include <QtCore/QSettings>
#include <QtCore/QTranslator>

#include <QtGui/QApplication>

#define ApplicationVersion "0.0.0.0"

#include "mainwindow.h"

int main (int argc, char ** argv)
{
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("System"));

	QApplication app (argc, argv);
	app.setOrganizationDomain ("panter.org");
	app.setOrganizationName ("PanteR");
	app.setApplicationName (QApplication::tr ("POCSLabComplex"));
	app.setApplicationVersion (ApplicationVersion);
//	app.setWindowIcon (QIcon (":share/images/main.ico"));

	QSettings::setDefaultFormat (QSettings::IniFormat);

	app.connect (&app, SIGNAL (lastWindowClosed ()), &app, SLOT (quit ()));

	MainWindow win;
	win.setWindowTitle (app.applicationName () + " " + app.applicationVersion ());

	win.show ();

	return app.exec ();
}
