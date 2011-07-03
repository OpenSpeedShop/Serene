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

#include "LineDataSeries.h"
#include "AbstractGraph/GraphWidget.h"

LineDataSeries::LineDataSeries(GraphWidget *parent) :
    DataSeries(parent)
{
}

void LineDataSeries::init(int column)
{
    glEnableClientState(GL_VERTEX_ARRAY);

    setListId(glGenLists(1));
    glNewList(listId(), GL_COMPILE);

    QColor color((Qt::GlobalColor)(Qt::red + column));
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

    glLineWidth(2);
    qsrand(QDateTime::currentMSecsSinceEpoch() * column);

    int points = 100;
    qreal space = 25.0/points;

    glBegin(GL_LINE_STRIP);
    float lastValue = (float)((qrand() % 100)/10);
    for(int index = 0; index < points+1; ++index) {
        float x = (float)(space * (index));

        qreal rand = ((qrand() % 100) * 0.025) - 1.25;
        float y = lastValue + (float)rand;
        if(y > 10.0) y = 10.0f;
        else if(y < 0.0) y = 0.0f;

        float z = -(float)(column * 0.01);
        glVertex3f(x,y,z);

        lastValue = y;
    }
    glEnd();

    glEndList();

    DataSeries::init(column);
}
