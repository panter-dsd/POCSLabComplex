#include <QtGui/QtEvents>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLayout>

#include "switchboarddialog.h"

SwitchboardDialog::SwitchboardDialog (QWidget *parent)
	: QDialog (parent)
{
	retranslateStrings ();
}

void SwitchboardDialog::retranslateStrings ()
{

}

bool SwitchboardDialog::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QDialog::event (ev);
}

void SwitchboardDialog::setInputCaptions (const QStringList& captions)
{
	m_inputCaptions = captions;
}

void SwitchboardDialog::setOutputCaptions (const QStringList& captions)
{
	m_outputCaptions = captions;
}

void SwitchboardDialog::setConnections (QMap <int, int> connections)
{
	m_connections = connections;
}
