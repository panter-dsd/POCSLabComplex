#include <QtGui/QTextEdit>
#include <QtGui/QtEvents>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLayout>

#include "reportdialog.h"

ReportDialog::ReportDialog (const QString& report, QWidget *parent)
	: QDialog (parent, Qt::WindowSystemMenuHint | Qt::WindowMaximizeButtonHint)
{
	edit = new QTextEdit (this);
	edit->setReadOnly (true);
	edit->setHtml (report);

	QDialogButtonBox *buttons = new QDialogButtonBox (QDialogButtonBox::Ok,
													  Qt::Horizontal,
													  this);
	connect (buttons, SIGNAL (accepted ()), this, SLOT (accept ()));

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->addWidget (edit);
	mainLayout->addWidget (buttons);
	setLayout (mainLayout);

	retranslateStrings ();
}

void ReportDialog::retranslateStrings ()
{
}

bool ReportDialog::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QDialog::event (ev);
}

