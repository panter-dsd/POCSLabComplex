#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QtEvents>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>

#include "inputdialog.h"
#include "operations.h"

InputDialog::InputDialog (QWidget *parent)
	: QDialog (parent)
{
	typeLabel = new QLabel (this);

	typeEdit = new QComboBox (this);
	typeEdit->setEditable(false);
	typeEdit->addItem("Hex", Hex);
	typeEdit->addItem("Dec", Dec);
	typeEdit->setCurrentIndex(-1);
	connect (typeEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));

	numbersCountLabel = new QLabel (this);

	numbersCountEdit = new QSpinBox (this);
	numbersCountEdit->setRange(1, 16);
	numbersCountEdit->setValue(16);

	valueLabel = new QLabel (this);

	valueEdit = new QLineEdit (this);
	valueEdit->setAlignment(Qt::AlignRight);
	connect (valueEdit, SIGNAL(textChanged(QString)), this, SLOT(valueChanged(QString)));

	outputValueLabel = new QLabel (this);

	outputValueEdit = new QLineEdit (this);
	outputValueEdit->setReadOnly(true);

	QDialogButtonBox *buttons = new QDialogButtonBox (QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
													  Qt::Horizontal,
													  this);
	connect (buttons, SIGNAL(accepted()), this, SLOT(accept()));
	connect (buttons, SIGNAL(rejected()), this, SLOT(reject()));

	QVBoxLayout *mainLayout = new QVBoxLayout ();
	mainLayout->addWidget(typeLabel);
	mainLayout->addWidget(typeEdit);
	mainLayout->addWidget(numbersCountLabel);
	mainLayout->addWidget(numbersCountEdit);
	mainLayout->addWidget(valueLabel);
	mainLayout->addWidget(valueEdit);
	mainLayout->addWidget(outputValueLabel);
	mainLayout->addWidget(outputValueEdit);
	mainLayout->addWidget(buttons);
	setLayout(mainLayout);

	typeEdit->setCurrentIndex(Dec);
	retranslateStrings();
}

void InputDialog::retranslateStrings()
{
	typeLabel->setText(tr ("Input type"));

	numbersCountLabel->setText(tr ("Numbers count"));

	valueLabel ->setText(tr ("Value"));
}

bool InputDialog::event(QEvent *ev)
{
	if (ev->type() == QEvent::LanguageChange) {
		retranslateStrings();
	}

	return QDialog::event(ev);
}

void InputDialog::indexChanged (int index)
{
	valueEdit->clear();
	switch (index) {
		case Hex:
			valueEdit->setInputMask("\\0\\xhhhh;0");
			break;
		case Dec:
			valueEdit->setInputMask("\\0\\,dddddd;0");
			break;
		default:
			valueEdit->setEnabled(false);
			return;
	}
	valueEdit->setFocus();
	valueEdit->setEnabled(true);
}

QByteArray InputDialog::value ()
{

}

void InputDialog::valueChanged (const QString& /*text*/)
{
	bool ok = false;
	switch (typeEdit->currentIndex()) {
		case Hex:
			outputValueEdit->setText("0." + Operations::decToBin((double) 1 / valueEdit->displayText().toLong(&ok, 16), numbersCountEdit->value()));
			break;
		case Dec: {
			outputValueEdit->setText("0." + Operations::decToBin(valueEdit->displayText().toDouble(), numbersCountEdit->value()));
			break;
		}
		default:
			outputValueEdit->clear();
			return;
	}
}
