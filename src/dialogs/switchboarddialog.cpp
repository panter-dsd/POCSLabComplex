#include <QtGui/QtEvents>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QComboBox>
#include <QtGui/QPushButton>
#include <QtGui/QListWidget>
#include <QtGui/QLabel>

#include "switchboarddialog.h"

SwitchboardDialog::SwitchboardDialog (QWidget *parent)
	: QDialog (parent)
{
	group = new QGroupBox (this);

	inputLabel = new QLabel (this);
	inputLabel->setAlignment (Qt::AlignHCenter);

	inputBox = new QComboBox (this);

	outputLabel = new QLabel (this);
	outputLabel->setAlignment (Qt::AlignHCenter);

	outputBox = new QComboBox (this);

	addButton = new QPushButton (this);
	connect (addButton, SIGNAL (clicked ()), this, SLOT (addSwitch ()));

	removeButton = new QPushButton (this);
	connect (removeButton, SIGNAL (clicked ()), this, SLOT (removeSwitch ()));

	switchesList = new QListWidget (this);

	QVBoxLayout *boxLayout = new QVBoxLayout ();
	boxLayout->addWidget (inputLabel);
	boxLayout->addWidget (inputBox);
	boxLayout->addWidget (outputLabel);
	boxLayout->addWidget (outputBox);
	boxLayout->addWidget (addButton);
	boxLayout->addWidget (removeButton);
	boxLayout->addSpacerItem (new QSpacerItem (0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding));
	group->setLayout (boxLayout);

	QDialogButtonBox *buttons = new QDialogButtonBox (QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
													  Qt::Horizontal,
													  this);
	connect (buttons, SIGNAL (accepted ()), this, SLOT (accept ()));
	connect (buttons, SIGNAL (rejected ()), this, SLOT (reject ()));

	QHBoxLayout *topLayout = new QHBoxLayout ();
	topLayout->addWidget (group);
	topLayout->addWidget (switchesList);

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->addLayout (topLayout);
	mainLayout->addWidget (buttons);
	setLayout (mainLayout);

	retranslateStrings ();
	updateSwitchesList ();
}

void SwitchboardDialog::retranslateStrings ()
{
	inputLabel->setText (tr ("Input"));
	outputLabel->setText (tr ("Output"));

	addButton->setText (tr ("Add"));
	removeButton->setText (tr ("Remove"));
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
	updateBoxes ();
}

void SwitchboardDialog::setOutputCaptions (const QStringList& captions)
{
	m_outputCaptions = captions;
	updateBoxes ();
}

void SwitchboardDialog::setConnections (QMap <int, int> connections)
{
	m_connections = connections;
	updateBoxes ();
	updateSwitchesList ();
}

void SwitchboardDialog::addSwitch ()
{
	if (inputBox->currentIndex () < 0 || outputBox->currentIndex () < 0) {
		return;
	}
	
	m_connections [m_inputCaptions.indexOf (inputBox->currentText ())] = m_outputCaptions.indexOf (outputBox->currentText ());
	updateSwitchesList ();
	updateBoxes ();
}

void SwitchboardDialog::removeSwitch ()
{
	QListWidgetItem *item = switchesList->currentItem ();
	if (!item) {
		return;
	}

	m_connections.remove (item->data (Qt::UserRole).toInt ());

	updateBoxes ();
	updateSwitchesList ();
}

void SwitchboardDialog::updateBoxes ()
{
	inputBox->clear ();
	outputBox->clear ();
	for (int i = 0; i < m_inputCaptions.size (); i++) {
		if (!m_inputCaptions [i].isEmpty () && !m_connections.contains (i)) {
			inputBox->addItem (m_inputCaptions [i]);
		}
	}
	for (int i = 0; i < m_outputCaptions.size (); i++) {
		if (!m_outputCaptions [i].isEmpty () && !m_connections.values ().contains (i)) {
			outputBox->addItem (m_outputCaptions [i]);
		}
	}
}

void SwitchboardDialog::updateSwitchesList ()
{
	QMapIterator <int, int> it (m_connections);
	switchesList->clear ();

	QListWidgetItem *item;
	while (it.hasNext ()) {
		it.next ();

		item = new QListWidgetItem (switchesList);
		item->setText (m_inputCaptions [it.key ()] + " -> " + m_outputCaptions [it.value ()]);
		item->setData (Qt::UserRole, it.key ());
		switchesList->addItem (item);
	}
}
