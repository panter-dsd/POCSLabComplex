#include <QtGui/QLabel>
#include <QtGui/QtEvents>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLayout>
#include <QtGui/QLineEdit>

#include "inputdialog.h"
#include "operations.h"

InputDialog::InputDialog (QWidget *parent)
	: QDialog (parent)
{
	positiveChanelLabel = new QLabel (this);

	positiveChanelEdit = new QLineEdit (this);
	positiveChanelEdit->setInputMask ("b\\.bbbbbbbbbbbbbbbb");
	connect (positiveChanelEdit, SIGNAL (textEdited (QString)), this, SLOT (valueChanged ()));

	negativeChanelLabel = new QLabel (this);

	negativeChanelEdit = new QLineEdit (this);
	negativeChanelEdit->setInputMask ("b\\.bbbbbbbbbbbbbbbb");
	connect (negativeChanelEdit, SIGNAL (textEdited (QString)), this, SLOT (valueChanged ()));

	dizssLabel = new QLabel (this);

	QDialogButtonBox *buttons = new QDialogButtonBox (QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
													  Qt::Horizontal,
													  this);
	connect (buttons, SIGNAL (accepted ()), this, SLOT (accept ()));
	connect (buttons, SIGNAL (rejected ()), this, SLOT (reject ()));

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->addWidget (positiveChanelLabel);
	mainLayout->addWidget (positiveChanelEdit);
	mainLayout->addWidget (negativeChanelLabel);
	mainLayout->addWidget (negativeChanelEdit);
	mainLayout->addWidget (dizssLabel);
	mainLayout->addWidget (buttons);
	setLayout (mainLayout);

	retranslateStrings ();
}

void InputDialog::retranslateStrings ()
{
	positiveChanelLabel->setText (tr ("Positive chanel"));

	negativeChanelLabel->setText (tr ("Negative chanel"));
}

bool InputDialog::event (QEvent *ev)
{
	if (ev->type () == QEvent::LanguageChange) {
		retranslateStrings ();
	}

	return QDialog::event (ev);
}

QByteArray InputDialog::value ()
{
	return m_value;
}

void InputDialog::setValue (const QByteArray& value)
{
	m_value = value;

	QByteArray positive;
	QByteArray negative;

	Operations::dizssToChanels (m_value, &positive, &negative);

	positiveChanelEdit->setText (Operations::binToString (positive));
	positiveChanelEdit->setCursorPosition (0);
	negativeChanelEdit->setText (Operations::binToString (negative));
	negativeChanelEdit->setCursorPosition (0);
}

void InputDialog::valueChanged ()
{
	const QByteArray& positive = Operations::stringToBin (positiveChanelEdit->text ());
	const QByteArray& negative = Operations::stringToBin (negativeChanelEdit->text ());

	m_value = Operations::normalizeBin (Operations::dizssFromChanels (positive, negative));

	QString text = "<p>" + Operations::binToString (m_value) + "</p>";
	text = text.replace ("-1", "<span style=\"text-decoration: overline\">1</span>");
	dizssLabel->setText (text);
}
