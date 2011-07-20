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

    /* Remove any previous primitives that we have created */
    foreach(LineDataSeries *lineSeries, m_LineSeries) {
        m_Primitives.removeOne(lineSeries);
    }

    /* Remove any existing data sets */
    qDeleteAll(m_LineSeries);
    m_LineSeries.clear();

    /* Create and add each column */
    qreal maxValue = 0.0;
    qreal minValue = 0.0;
    int points = 10;
    for(int index = 0; index < 5; ++index) {
        LineDataSeries *lineSeries = new LineDataSeries(this);
        m_LineSeries.append(lineSeries);

        lineSeries->setColumn(index);
        lineSeries->setColor(QColor((Qt::GlobalColor)(Qt::red + index)));

        //DEBUG: This is for debugging purposes only
        lineSeries->randomizeData(points);

        /* Check each point to see if it redifines our boundaries */
        foreach(QVariant data, lineSeries->data()) {
            qreal value = data.toReal();
            if(maxValue < value) maxValue = value;
            if(minValue > value) minValue = value;
        }
    }

    /* Set the max and min values that we found in the previous loop */
    m_BoundingCube.setMaxValue(maxValue);
    m_BoundingCube.setMinValue(minValue);

    /* Setup the horizontal axis */
    QList<QString> xLabels;
    for(int index = 0; index < points; ++index) {
        xLabels.append(tr("Function_%1").arg(index));
    }
    m_GridLine2D.setXLabels(xLabels);

    /* Setup the vertical axis */
    QList<QString> yLabels;
    points = 5;
    qreal interval = (maxValue - minValue) / points;
    for(int index = 0; index <= points; ++index) {
        qreal value = minValue + (interval * index);
        yLabels.append(QString::number(value));
    }
    m_GridLine2D.setYLabels(yLabels);

    /* Set the bounding cuboid, and initialize each series */
    foreach(LineDataSeries *lineSeries, m_LineSeries) {
        lineSeries->setBoundingCube(&m_BoundingCube);
        lineSeries->init();
        m_Primitives.append(lineSeries);
    }
}
