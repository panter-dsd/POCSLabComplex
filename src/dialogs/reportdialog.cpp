#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <QtGui/QTextEdit>
#include <QtGui/QtEvents>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLayout>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QPrintDialog>
#include <QtGui/QPrinter>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QStyle>

#include "reportdialog.h"

ReportDialog::ReportDialog (const QString& report, QWidget *parent)
	: QDialog (parent, Qt::WindowSystemMenuHint | Qt::WindowMaximizeButtonHint), m_report (report)
{
	edit = new QTextEdit (this);
	edit->setReadOnly (true);
	edit->setHtml (report);

	toolBar = new QToolBar (this);

	QDialogButtonBox *buttons = new QDialogButtonBox (QDialogButtonBox::Ok,
													  Qt::Horizontal,
													  this);
	connect (buttons, SIGNAL (accepted ()), this, SLOT (accept ()));

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->addWidget (toolBar);
	mainLayout->addWidget (edit);
	mainLayout->addWidget (buttons);
	setLayout (mainLayout);

	actionPrint = new QAction (this);
	actionPrint->setShortcut (QKeySequence::Print);
	actionPrint->setIcon (QIcon(":/share/images/print.png"));
	connect (actionPrint, SIGNAL (triggered ()), this, SLOT (print ()));
	toolBar->addAction (actionPrint);

	actionExportToHtml = new QAction (this);
	actionExportToHtml->setIcon (style ()->standardIcon (QStyle::SP_DialogSaveButton));
	connect (actionExportToHtml, SIGNAL (triggered ()), this, SLOT (exportToHtml ()));
	toolBar->addAction (actionExportToHtml);

	retranslateStrings ();
}

void ReportDialog::retranslateStrings ()
{
	actionPrint->setText (tr ("Print"));
	actionExportToHtml->setText (tr ("Export to html"));
}

bool ReportDialog::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QDialog::event (ev);
}

void ReportDialog::print ()
{
	QPrinter printer;

	QPrintDialog d (&printer, this);

	if (d.exec ()) {
		edit->print (&printer);
	}	
}

void ReportDialog::exportToHtml ()
{
	const QString& fileName = QFileDialog::getSaveFileName (this, 
															tr ("Export"),
															"",
															tr ("Html files (*.html)"));
	if (!fileName.isEmpty ()) {
		saveHtml (fileName);
	}
}

void ReportDialog::saveHtml (const QString& fileName)
{
	QFile file (fileName);

	if (!file.open (QIODevice::WriteOnly)) {
		QMessageBox::critical (this, "", tr ("Error write file"));
		return;
	}

	QTextStream stream (&file);

	stream << m_report;
	file.close ();
}
