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

#ifndef LINEGRAPHWIDGET_H
#define LINEGRAPHWIDGET_H

#include "Graph2D/GraphWidget2D.h"
#include "LineDataSeries.h"

namespace Serene {

class LineGraphWidget : public GraphWidget2D
{
    Q_OBJECT
public:
    explicit LineGraphWidget(QWidget *parent = 0);
    ~LineGraphWidget();

    QList<LineDataSeries *> *lineSeries() { return &m_LineSeries; }

    void setXLabels(const QList<QString> &xLabels) { m_GridLine.setXLabels(xLabels); }
    void setYLabels(const QList<QString> &yLabels) { m_GridLine.setYLabels(yLabels); }

    void clearData();
    void addColumn(const QList<QVariant> &data);

protected:
    virtual void init();

private:
    QList<LineDataSeries *> m_LineSeries;

};

} // namespace Serene

#endif // LINEGRAPHWIDGET_H
