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

#include "DataSeries.h"

namespace Serene {

DataSeries::DataSeries(QObject *parent) :
    BoundedPrimitive(parent),
    m_Column(-1)
{
}

void DataSeries::init()
{
    BoundedPrimitive::init();
}

int DataSeries::column()
{
    return m_Column;
}

void DataSeries::setColumn(int column)
{
    m_Column = column;
    emit columnChanged();
}


QList<QVariant> DataSeries::data() const
{
    return m_Data;
}

void DataSeries::setData(const QList<QVariant> &data)
{
    m_Data = data;
    emit dataChanged();
}

void DataSeries::randomizeData(int points)
{
    QList<QVariant> randomData;
    qsrand(QDateTime::currentMSecsSinceEpoch() * column());
    for(int index = 0; index < points; ++index) {
        randomData.append(QVariant((qreal)qrand()));
    }
    setData(randomData);
}

QColor DataSeries::color() const
{
    return m_Color;
}

void DataSeries::setColor(const QColor &color)
{
    m_Color = color;
    emit colorChanged();
}

} // namespace Serene
