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
* along with Panther Commander; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA 02110-1301 USA
*-------------------------------------------------------------------
* Project:POCSLabComplex
* Author:PanteR
* Contact:panter.dsd@gmail.com
*******************************************************************/

#ifndef ALB1BLOCK_H
#define ALB1BLOCK_H

#include "abstractblock.h"

class Alb1Block : public AbstractBlock
{
	Q_OBJECT

public:
	Alb1Block (const QString& caption = 0, QWidget *parent = 0);

private:
	void updateToolTip ();

public Q_SLOTS:
	void chooseOperation ();
};

#endif // ALB1BLOCK_H
