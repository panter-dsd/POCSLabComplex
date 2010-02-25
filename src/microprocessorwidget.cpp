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

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QPen>
#include <QtGui/QInputDialog>
#include <QtGui/QAction>

#include "microprocessorwidget.h"
#include "abstractblock.h"
#include "alb1block.h"
#include "alb2block.h"
#include "alb3block.h"
#include "mb1block.h"
#include "mb2block.h"

MicroprocessorWidget::MicroprocessorWidget(QWidget *parent)
	:QWidget(parent), m_scheme(-1)
{
//	setFixedSize(500, 300);

	actionChooseScheme = new QAction(tr("Choose scheme"), this);
	connect(actionChooseScheme, SIGNAL(triggered()), this, SLOT(chooseScheme()));
	addAction(actionChooseScheme);

	setContextMenuPolicy(Qt::ActionsContextMenu);

	alb1 = new Alb1Block(tr("ALB1"), this);
	alb2 = new Alb2Block(tr("ALB2"), this);
	alb3 = new Alb3Block(tr("ALB3"), this);
	mb1 = new Mb1Block(tr("MB1"), this);
	mb2 = new Mb2Block(tr("MB2"), this);

	updateWidgets();
}

void MicroprocessorWidget::resizeEvent(QResizeEvent */*ev*/)
{
	foreach(AbstractBlock *ab, findChildren<AbstractBlock*> ()) {
		ab->setFixedSize(width() / 5, height() / 5);
	}

	switch (m_scheme) {
	case 0:
		resize_0();
		break;
	case 1:
		resize_1();
		break;
	case 2:
		resize_2();
		break;
	}
}

void MicroprocessorWidget::resize_0()
{
	alb1->move(width() / 2 - alb1->width() / 2, 20);
	alb2->move(width() / 2 - alb1->width() / 2, height() / 2 + alb2->height() / 2);
	alb3->move(width() - alb3->width() - 60, alb1->y() + alb1->height());
	mb1->move(60, height() / 2 - mb1->height() / 2);
	mb2->move(60, height() / 2 + mb1->height() / 2 + 40);
}

void MicroprocessorWidget::resize_1()
{
	alb1->move(width() / 2 - alb1->width() / 2, 20);
	alb2->move(width() / 2 - alb1->width() / 2, height() / 2 + alb2->height() / 2);
	alb3->move(width() - alb3->width() - 60, alb1->y() + alb1->height());
	mb1->move(60, height() / 2 - mb1->height() / 2);
	mb2->move(60, height() / 2 + mb1->height() / 2 + 40);
}

void MicroprocessorWidget::resize_2()
{
	alb1->move(width() / 2 - alb1->width() / 2, 20);
	alb2->move(width() / 2 - alb1->width() / 2, height() / 2 + alb2->height() / 2);
	alb3->move(width() - alb3->width() - 60, alb1->y() + alb1->height());
	mb1->move(60, height() / 2 - mb1->height() / 2);
	mb2->move(60, height() / 2 + mb1->height() / 2 + 40);
}

void MicroprocessorWidget::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);

	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::darkGray);
	pen.setWidth(7);
	painter.setPen(pen);

	QRect m_rect(rect().x() + fontMetrics().width("WWWW"), rect().top() + fontMetrics().height() * 2, rect().width() - fontMetrics().width("WWWW"), rect().height() - fontMetrics().height() * 2);

	//Shadow
	painter.drawLine(m_rect.x() + pen.width(), m_rect.y() + m_rect.height() - pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());
	painter.drawLine(m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + pen.width(), m_rect.x() + m_rect.width() - pen.width(), m_rect.y() + m_rect.height() - pen.width());

	//Rect
	pen.setBrush(Qt::black);
	painter.setPen(pen);
	m_rect.setWidth(m_rect.width() - pen.width() * 2);
	m_rect.setHeight(m_rect.height() - pen.width() * 2);
	painter.drawRect(m_rect);

	//Draw caption

	const QString caption = tr("MP 4.601V ZHZ - 0034 Scheme %1").arg(m_scheme >= 0 ? QString::number(m_scheme) : "");
	painter.drawText(width() / 2 - fontMetrics().width(caption) / 2, fontMetrics().height(), caption);

	switch (m_scheme) {
	case 0:
		paint_0(ev, &painter);
		break;
	case 1:
		paint_1(ev, &painter);
		break;
	case 2:
		paint_2(ev, &painter);
		break;
	}
}

void MicroprocessorWidget::paint_0(QPaintEvent */*ev*/, QPainter *painter)
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);

	//A0 -> ALB1
	painter->drawLine(0, alb1->y() + alb1->height() / 3, alb1->x(), alb1->y() + alb1->height() / 3);
	//A1 -> ALB1
	painter->drawLine(0, alb1->y() + alb1->height() / 3 * 2, alb1->x(), alb1->y() + alb1->height() / 3 * 2);
	//A2 -> MB1
	painter->drawLine(0, mb1->y() + mb1->height() / 3, mb1->x(), mb1->y() + mb1->height() / 3);
	//A3 -> MB1
	painter->drawLine(0, mb1->y() + mb1->height() / 3 * 2, mb1->x(), mb1->y() + mb1->height() / 3 * 2);
	//A4 -> MB2
	painter->drawLine(0, mb2->y() + mb2->height() / 3, mb2->x(), mb2->y() + mb2->height() / 3);
	//A5 -> MB2
	painter->drawLine(0, mb2->y() + mb2->height() / 3 * 2, mb2->x(), mb2->y() + mb2->height() / 3 * 2);
	//ALB1 -> Q1
	painter->drawLine(alb1->x() + alb1->width(), alb1->y() + alb1->height() / 3, width(), alb1->y() + alb1->height() / 3);
	//ALB1 -> ALB3
	painter->drawLine(alb1->x() + alb1->width() + 20, alb1->y() + alb1->height() / 3, alb1->x() + alb1->width() + 20, alb3->y() + alb3->height() / 3 * 2);
	painter->drawLine(alb1->x() + alb1->width() + 20, alb3->y() + alb3->height() / 3 * 2, alb3->x(), alb3->y() + alb3->height() / 3 * 2);
	//MB1 -> Q5
	painter->drawLine(mb1->x() + mb1->width(), mb1->y() + mb1->height() / 3, alb2->x(), mb1->y() + mb1->height() / 3);
	painter->drawLine(alb2->x(), mb1->y() + mb1->height() / 3, alb2->x(), mb1->y() + mb1->height() / 3 * 2);
	painter->drawLine(alb2->x(), mb1->y() + mb1->height() / 3 * 2, width(), mb1->y() + mb1->height() / 3 * 2);
	//MB1 -> ALB2
	painter->drawLine(mb1->x() + mb1->width(), mb1->y() + mb1->height() / 3 * 2, mb1->x() + mb1->width() + 20, mb1->y() + mb1->height() / 3 * 2);
	painter->drawLine(mb1->x() + mb1->width() + 20, mb1->y() + mb1->height() / 3 * 2, mb1->x() + mb1->width() + 20, alb2->y() + alb2->height() / 3);
	painter->drawLine(mb1->x() + mb1->width() + 20, alb2->y() + alb2->height() / 3, alb2->x(), alb2->y() + alb2->height() / 3);
	//MB2 -> ALB2
	painter->drawLine(mb2->x() + mb2->width(), mb2->y() + mb2->height() / 3, mb2->x() + mb2->width() + 20, mb2->y() + mb2->height() / 3);
	painter->drawLine(mb2->x() + mb2->width() + 20, mb2->y() + mb2->height() / 3, mb2->x() + mb2->width() + 20, alb2->y() + alb2->height() / 3 * 2);
	painter->drawLine(mb2->x() + mb2->width() + 20, alb2->y() + alb2->height() / 3 * 2, alb2->x(), alb2->y() + alb2->height() / 3 * 2);
	//MB2 -> Q4
	painter->drawLine(mb2->x() + mb2->width(), mb2->y() + mb2->height() / 3 * 2, width(), mb2->y() + mb2->height() / 3 * 2);
	//ALB2 -> Q6
	painter->drawLine(alb2->x() + alb2->width(), alb2->y() + alb2->height() / 3, width(), alb2->y() + alb2->height() / 3);
	//ALB2 -> ALB3
	painter->drawLine(alb2->x() + alb2->width() + 10, alb2->y() + alb2->height() / 3, alb2->x() + alb2->width() + 10, alb3->y() + alb3->height() / 3);
	painter->drawLine(alb2->x() + alb2->width() + 10, alb3->y() + alb3->height() / 3, alb3->x(), alb3->y() + alb3->height() / 3);
	//ALB2 -> Qsign
	painter->drawLine(alb2->x() + alb2->width(), alb2->y() + alb2->height() / 3 * 2, alb3->x() + alb3->width(), alb2->y() + alb2->height() / 3 * 2);
	//ALB3 -> Q2
	painter->drawLine(alb3->x() + alb3->width(), alb3->y() + alb3->height() / 3, width(), alb3->y() + alb3->height() / 3);

	//A0 text
	painter->drawText(0, alb1->y() + alb1->height() / 3 - fontMetrics().height() / 2, "A0");
	//A1 text
	painter->drawText(0, alb1->y() + alb1->height() / 3 * 2 - fontMetrics().height() / 2, "A1");
	//A2 text
	painter->drawText(0, mb1->y() + mb1->height() / 3 - fontMetrics().height() / 2, "A2");
	//A3 text
	painter->drawText(0, mb1->y() + mb1->height() / 3 * 2 - fontMetrics().height() / 2, "A3");
	//A4 text
	painter->drawText(0, mb2->y() + mb2->height() / 3 - fontMetrics().height() / 2, "A4");
	//A5 text
	painter->drawText(0, mb2->y() + mb2->height() / 3 * 2 - fontMetrics().height() / 2, "A5");
}

void MicroprocessorWidget::paint_1(QPaintEvent */*ev*/, QPainter *painter)
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);

	//A0 -> ALB1
	painter->drawLine(0, alb1->y() + alb1->height() / 3, alb1->x(), alb1->y() + alb1->height() / 3);
	//A1 -> ALB1
	painter->drawLine(0, alb1->y() + alb1->height() / 3 * 2, alb1->x(), alb1->y() + alb1->height() / 3 * 2);
	//A2 -> MB1
	painter->drawLine(0, mb1->y() + mb1->height() / 3, mb1->x(), mb1->y() + mb1->height() / 3);
	//A3 -> MB1
	painter->drawLine(0, mb1->y() + mb1->height() / 3 * 2, mb1->x(), mb1->y() + mb1->height() / 3 * 2);
	//A4 -> MB2
	painter->drawLine(0, mb2->y() + mb2->height() / 3, mb2->x(), mb2->y() + mb2->height() / 3);
	//A1 -> MB2
	painter->drawLine(mb2->x() - 10, alb1->y() + alb1->height() / 3 * 2, mb2->x() -10, mb2->y() + mb2->height() / 3 * 2);
	painter->drawLine(mb2->x() -10, mb2->y() + mb2->height() / 3 * 2, mb2->x(), mb2->y() + mb2->height() / 3 * 2);
	//ALB1 -> Q1
	painter->drawLine(alb1->x() + alb1->width(), alb1->y() + alb1->height() / 3, width(), alb1->y() + alb1->height() / 3);
	//ALB1 -> ALB3
	painter->drawLine(alb1->x() + alb1->width() + 20, alb1->y() + alb1->height() / 3, alb1->x() + alb1->width() + 20, alb3->y() + alb3->height() / 3 * 2);
	painter->drawLine(alb1->x() + alb1->width() + 20, alb3->y() + alb3->height() / 3 * 2, alb3->x(), alb3->y() + alb3->height() / 3 * 2);
	//MB1 -> Q5
	painter->drawLine(mb1->x() + mb1->width(), mb1->y() + mb1->height() / 3, alb2->x(), mb1->y() + mb1->height() / 3);
	painter->drawLine(alb2->x(), mb1->y() + mb1->height() / 3, alb2->x(), mb1->y() + mb1->height() / 3 * 2);
	painter->drawLine(alb2->x(), mb1->y() + mb1->height() / 3 * 2, width(), mb1->y() + mb1->height() / 3 * 2);
	//MB1 -> ALB2
	painter->drawLine(mb1->x() + mb1->width(), mb1->y() + mb1->height() / 3 * 2, mb1->x() + mb1->width() + 20, mb1->y() + mb1->height() / 3 * 2);
	painter->drawLine(mb1->x() + mb1->width() + 20, mb1->y() + mb1->height() / 3 * 2, mb1->x() + mb1->width() + 20, alb2->y() + alb2->height() / 3);
	painter->drawLine(mb1->x() + mb1->width() + 20, alb2->y() + alb2->height() / 3, alb2->x(), alb2->y() + alb2->height() / 3);
	//MB2 -> ALB2
	painter->drawLine(mb2->x() + mb2->width(), mb2->y() + mb2->height() / 3, mb2->x() + mb2->width() + 20, mb2->y() + mb2->height() / 3);
	painter->drawLine(mb2->x() + mb2->width() + 20, mb2->y() + mb2->height() / 3, mb2->x() + mb2->width() + 20, alb2->y() + alb2->height() / 3 * 2);
	painter->drawLine(mb2->x() + mb2->width() + 20, alb2->y() + alb2->height() / 3 * 2, alb2->x(), alb2->y() + alb2->height() / 3 * 2);
	//MB2 -> Q4
	painter->drawLine(mb2->x() + mb2->width(), mb2->y() + mb2->height() / 3 * 2, width(), mb2->y() + mb2->height() / 3 * 2);
	//ALB2 -> Q6
	painter->drawLine(alb2->x() + alb2->width(), alb2->y() + alb2->height() / 3, width(), alb2->y() + alb2->height() / 3);
	//ALB2 -> ALB3
	painter->drawLine(alb2->x() + alb2->width() + 10, alb2->y() + alb2->height() / 3, alb2->x() + alb2->width() + 10, alb3->y() + alb3->height() / 3);
	painter->drawLine(alb2->x() + alb2->width() + 10, alb3->y() + alb3->height() / 3, alb3->x(), alb3->y() + alb3->height() / 3);
	//ALB2 -> Qsign
	painter->drawLine(alb2->x() + alb2->width(), alb2->y() + alb2->height() / 3 * 2, alb3->x() + alb3->width(), alb2->y() + alb2->height() / 3 * 2);
	//ALB3 -> Q2
	painter->drawLine(alb3->x() + alb3->width(), alb3->y() + alb3->height() / 3, width(), alb3->y() + alb3->height() / 3);

	//A0 text
	painter->drawText(0, alb1->y() + alb1->height() / 3 - fontMetrics().height() / 2, "A0");
	//A1 text
	painter->drawText(0, alb1->y() + alb1->height() / 3 * 2 - fontMetrics().height() / 2, "A1");
	//A2 text
	painter->drawText(0, mb1->y() + mb1->height() / 3 - fontMetrics().height() / 2, "A2");
	//A3 text
	painter->drawText(0, mb1->y() + mb1->height() / 3 * 2 - fontMetrics().height() / 2, "A3");
	//A4 text
	painter->drawText(0, mb2->y() + mb2->height() / 3 - fontMetrics().height() / 2, "A4");
}

void MicroprocessorWidget::paint_2(QPaintEvent */*ev*/, QPainter *painter)
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setBrush(Qt::black);
	pen.setWidth(1);
	painter->setPen(pen);

	//A0 -> ALB1
	painter->drawLine(0, alb1->y() + alb1->height() / 3, alb1->x(), alb1->y() + alb1->height() / 3);
	//A1 -> ALB1
	painter->drawLine(0, alb1->y() + alb1->height() / 3 * 2, alb1->x(), alb1->y() + alb1->height() / 3 * 2);
	//A2 -> MB1
	painter->drawLine(0, mb1->y() + mb1->height() / 3, mb1->x(), mb1->y() + mb1->height() / 3);
	//A3 -> MB1
	painter->drawLine(0, mb1->y() + mb1->height() / 3 * 2, mb1->x(), mb1->y() + mb1->height() / 3 * 2);
	//A4 -> MB2
	painter->drawLine(0, mb2->y() + mb2->height() / 3, mb2->x(), mb2->y() + mb2->height() / 3);
	//A5 -> MB2
	painter->drawLine(0, mb2->y() + mb2->height() / 3 * 2, mb2->x(), mb2->y() + mb2->height() / 3 * 2);
	//ALB1 -> ALB3
	painter->drawLine(alb1->x() + alb1->width(), alb1->y() + alb1->height() / 3, alb1->x() + alb1->width() + 20,  alb1->y() + alb1->height() / 3);
	painter->drawLine(alb1->x() + alb1->width() + 20, alb1->y() + alb1->height() / 3, alb1->x() + alb1->width() + 20, alb3->y() + alb3->height() / 3 * 2);
	painter->drawLine(alb1->x() + alb1->width() + 20, alb3->y() + alb3->height() / 3 * 2, alb3->x(), alb3->y() + alb3->height() / 3 * 2);
	//MB1 -> Q5
	painter->drawLine(mb1->x() + mb1->width(), mb1->y() + mb1->height() / 3, alb2->x(), mb1->y() + mb1->height() / 3);
	painter->drawLine(alb2->x(), mb1->y() + mb1->height() / 3, alb2->x(), mb1->y() + mb1->height() / 3 * 2);
	painter->drawLine(alb2->x(), mb1->y() + mb1->height() / 3 * 2, width(), mb1->y() + mb1->height() / 3 * 2);
	//MB1 -> ALB2
	painter->drawLine(mb1->x() + mb1->width(), mb1->y() + mb1->height() / 3 * 2, mb1->x() + mb1->width() + 20, mb1->y() + mb1->height() / 3 * 2);
	painter->drawLine(mb1->x() + mb1->width() + 20, mb1->y() + mb1->height() / 3 * 2, mb1->x() + mb1->width() + 20, alb2->y() + alb2->height() / 3);
	painter->drawLine(mb1->x() + mb1->width() + 20, alb2->y() + alb2->height() / 3, alb2->x(), alb2->y() + alb2->height() / 3);
	//MB2 -> ALB2
	painter->drawLine(mb2->x() + mb2->width(), mb2->y() + mb2->height() / 3, mb2->x() + mb2->width() + 20, mb2->y() + mb2->height() / 3);
	painter->drawLine(mb2->x() + mb2->width() + 20, mb2->y() + mb2->height() / 3, mb2->x() + mb2->width() + 20, alb2->y() + alb2->height() / 3 * 2);
	painter->drawLine(mb2->x() + mb2->width() + 20, alb2->y() + alb2->height() / 3 * 2, alb2->x(), alb2->y() + alb2->height() / 3 * 2);
	//MB2 -> Q4
	painter->drawLine(mb2->x() + mb2->width(), mb2->y() + mb2->height() / 3 * 2, width(), mb2->y() + mb2->height() / 3 * 2);
	//ALB2 -> Q6
	painter->drawLine(alb2->x() + alb2->width(), alb2->y() + alb2->height() / 3, width(), alb2->y() + alb2->height() / 3);
	//ALB2 -> ALB3
	painter->drawLine(alb2->x() + alb2->width() + 10, alb2->y() + alb2->height() / 3, alb2->x() + alb2->width() + 10, alb3->y() + alb3->height() / 3);
	painter->drawLine(alb2->x() + alb2->width() + 10, alb3->y() + alb3->height() / 3, alb3->x(), alb3->y() + alb3->height() / 3);
	//ALB2 -> Qsign
	painter->drawLine(alb2->x() + alb2->width(), alb2->y() + alb2->height() / 3 * 2, alb3->x() + alb3->width(), alb2->y() + alb2->height() / 3 * 2);
	//ALB3 -> Q2
	painter->drawLine(alb3->x() + alb3->width(), alb3->y() + alb3->height() / 3, width(), alb3->y() + alb3->height() / 3);
	//MB1 -> Q1
	painter->drawLine(alb3->x() + alb3->width(), mb1->y() + mb1->height() / 3 * 2, alb3->x() + alb3->width(), mb1->y() + mb1->height() / 3);
	painter->drawLine(alb3->x() + alb3->width(), mb1->y() + mb1->height() / 3, width(), mb1->y() + mb1->height() / 3);

	//A0 text
	painter->drawText(0, alb1->y() + alb1->height() / 3 - fontMetrics().height() / 2, "A0");
	//A1 text
	painter->drawText(0, alb1->y() + alb1->height() / 3 * 2 - fontMetrics().height() / 2, "A1");
	//A2 text
	painter->drawText(0, mb1->y() + mb1->height() / 3 - fontMetrics().height() / 2, "A2");
	//A3 text
	painter->drawText(0, mb1->y() + mb1->height() / 3 * 2 - fontMetrics().height() / 2, "A3");
	//A4 text
	painter->drawText(0, mb2->y() + mb2->height() / 3 - fontMetrics().height() / 2, "A4");
	//A5 text
	painter->drawText(0, mb2->y() + mb2->height() / 3 * 2 - fontMetrics().height() / 2, "A5");
}

void MicroprocessorWidget::chooseScheme()
{
	QStringList schemes;
	schemes << "0" << "1" << "2" << "4" << "5" << "6";

	const int currentScheme = schemes.indexOf(QString::number(m_scheme));

	bool ok = false;

	const QString& scheme = QInputDialog::getItem(this, tr("Choose scheme"), tr("Scheme"), schemes, currentScheme, false, &ok);

	if (ok && !scheme.isEmpty()) {
		m_scheme = scheme.toInt();
		updateWidgets();
		resizeEvent(0);
	}
}

void MicroprocessorWidget::updateWidgets()
{
	alb1->setVisible(m_scheme >= 0);
	alb2->setVisible(m_scheme >= 0);
	alb3->setVisible(m_scheme >= 0);
	mb1->setVisible(m_scheme >= 0);
	mb2->setVisible(m_scheme >= 0);
}
