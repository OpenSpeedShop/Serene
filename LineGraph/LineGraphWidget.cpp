/*!
   \file
   \author Dane Gardner <dane.gardner@gmail.com>
   \version

   \section LICENSE
   This file is part of the Serene 3D Graphing Library
   Copyright (C) 2010-2011 Argo Navis Technologies, LLC

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 2.1 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
   for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this library; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

   \section DESCRIPTION

 */

#include "LineGraphWidget.h"

LineGraphWidget::LineGraphWidget(QWidget *parent) :
    GraphWidget2D(parent)
{
}

LineGraphWidget::~LineGraphWidget()
{
    qDeleteAll(m_LineSeries);
    m_LineSeries.clear();
}

void LineGraphWidget::init()
{
    GraphWidget2D::init();

    // Remove any previous primitives that we have created
    foreach(LineDataSeries *lineSeries, m_LineSeries) {
        m_Primitives.removeOne(lineSeries);
    }
    qDeleteAll(m_LineSeries);
    m_LineSeries.clear();

    // Create and add each column
    for(int i=0; i<5; ++i) {
        LineDataSeries *lineSeries = new LineDataSeries(this);
        lineSeries->init(i);
        m_Primitives.append(lineSeries);
        m_LineSeries.append(lineSeries);
    }
}
