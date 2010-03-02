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

#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QtCore/QMap>

#include <QtGui/QWidget>

class AbstractBlock : public QWidget {

	Q_OBJECT

protected:
	QString m_caption;
	QByteArray m_firstValue;
	QByteArray m_secondValue;
	bool m_isModule;
	char m_operation;
	QMap<char, QString> operations;
	QMap<char, QString> moduleOperations;

public:
	AbstractBlock(const QString& caption = 0, QWidget *parent = 0);
	virtual ~AbstractBlock()
	{}

	QString caption() const
	{ return m_caption; }
	void setCaption(const QString& caption)
	{
		m_caption = caption;
		updateToolTip();
	}

	bool isModule() const
	{ return m_isModule; }
	void setIsModule(bool b)
	{ m_isModule = b; }

	char operation() const
	{ return m_operation; }
	void setOperation(char operation)
	{
		m_operation = operation;
		updateToolTip();
	}

	bool isValid() const
	{ return m_operation >= 0; }

protected:
	void paintEvent(QPaintEvent *ev);
	void mouseDoubleClickEvent(QMouseEvent *ev);
	virtual void updateToolTip();

public Q_SLOTS:
	void setFirstValue(const QByteArray& value);
	void setSecondValue(const QByteArray& value);
	virtual void chooseOperation()
	{}

Q_SIGNALS:
	void valueChanged(const QByteArray& newValue);
	void operationChanged(char newOperation);
};

#endif //ABSTRACTBLOCK_H
