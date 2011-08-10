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

namespace Serene {

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

//    /* Setup the vertical axis */
//    QList<QString> yLabels;
//    int points = 5;
//    qreal interval = (maxValue - minValue) / points;
//    for(int index = 0; index <= points; ++index) {
//        qreal value = minValue + (interval * index);
//        yLabels.append(QString::number(value));
//    }
//    m_GridLine.setYLabels(yLabels);

}

void LineGraphWidget::clearData()
{
    /* Remove any previous primitives that we have created */
    qDeleteAll(m_Primitives);
    m_Primitives.clear();

    /* Remove any existing data sets */
    qDeleteAll(m_LineSeries);
    m_LineSeries.clear();

    /* Set the max and min values that we found in the previous loop */
    m_BoundingCube.setMaxValue(0.0);
    m_BoundingCube.setMinValue(0.0);
}

void LineGraphWidget::addColumn(const QList<QVariant> &data)
{
    /* Build the displayed series */
    LineDataSeries *lineSeries = new LineDataSeries(this);
    lineSeries->setColumn(m_LineSeries.count());
    lineSeries->setColor(QColor((Qt::GlobalColor)(Qt::red + lineSeries->column())));
    lineSeries->setData(data);
    m_LineSeries.append(lineSeries);

    /* Check each point to see if it redifines our boundaries */
    qreal maxValue = m_BoundingCube.maxValue();
    qreal minValue = m_BoundingCube.minValue();
    foreach(QVariant dataPoint, data) {
        qreal value = dataPoint.toReal();
        if(maxValue < value) maxValue = value;
        if(minValue > value) minValue = value;
    }

    /* Set the max and min values that we found in the previous loop */
    m_BoundingCube.setMaxValue(maxValue);
    m_BoundingCube.setMinValue(minValue);

    /* Set the bounding cuboid, and initialize each series */
    lineSeries->setBoundingCube(&m_BoundingCube);
    lineSeries->init();
    m_Primitives.append(lineSeries);
}

} // namespace Serene
