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

#include <QDebug>

LineDataSeries::LineDataSeries(QObject *parent) :
    DataSeries(parent)
{
}

void LineDataSeries::init()
{
    if(!isValid()) {
        connect(this, SIGNAL(columnChanged()), this, SLOT(rebuild()));
        connect(this, SIGNAL(dataChanged()), this, SLOT(rebuild()));
        connect(this, SIGNAL(colorChanged()), this, SLOT(rebuild()));
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    if(listId() > 0) {
        glDeleteLists(listId(), 1);
        setListId(0);
    }

    setListId(glGenLists(1));
    glNewList(listId(), GL_COMPILE);

    QColor color = this->color();
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

    glLineWidth(2);

    int points = data().count() - 1;
    qreal width = boundingCube()->width();
    qreal height = boundingCube()->height();

    qreal maxValue = boundingCube()->maxValue();
    qreal minValue = boundingCube()->minValue();

    glBegin(GL_LINE_STRIP);
    int index = -1;
    foreach(QVariant dataPoint, data()) {
        ++index;

        bool okay = false;
        qreal dataValue = dataPoint.toReal(&okay);

        if(!okay) {
            dataValue = (qreal(dataPoint.toLongLong(&okay)));
        }

        if(!okay) {
            qWarning("Datapoint not an expected data type");
            continue;
        }

        qreal x = (width / points) * index;

        qreal percentOfDelta = (dataValue != minValue)? (dataValue - minValue) / (maxValue - minValue): 0.0;
        qreal y = height * percentOfDelta;

        qreal z = -(column() * 0.01);

        if(sizeof(qreal) == sizeof(float)) {
            glVertex3f(x, y, z);
        } else {
            glVertex3d(x, y, z);
        }
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    index = -1;
    foreach(QVariant dataPoint, data()) {
        ++index;

        bool okay = false;
        qreal dataValue = dataPoint.toReal(&okay);

        if(!okay) {
            dataValue = (qreal(dataPoint.toLongLong(&okay)));
        }

        if(!okay) {
            qWarning("Datapoint not an expected data type");
            continue;
        }

        qreal x = (width / points) * index;

        qreal percentOfDelta = (dataValue != minValue)? (dataValue - minValue) / (maxValue - minValue): 0.0;
        qreal y = height * percentOfDelta;

        qreal z = -(column() * 0.01);

        if(sizeof(qreal) == sizeof(float)) {
            glVertex3f(x, y, z);
        } else {
            glVertex3d(x, y, z);
        }
    }
    glEnd();

    glEndList();

    DataSeries::init();
}

void LineDataSeries::pickRender()
{
    int points = data().count() - 1;
    qreal width = boundingCube()->width();
    qreal height = boundingCube()->height();

    qreal maxValue = boundingCube()->maxValue();
    qreal minValue = boundingCube()->minValue();

    glPointSize(7.5f);

    glPushName(column());
    int index = -1;
    foreach(QVariant dataPoint, data()) {
        ++index;

        bool okay = false;
        qreal dataValue = dataPoint.toReal(&okay);

        if(!okay) {
            dataValue = (qreal(dataPoint.toLongLong(&okay)));
        }

        if(!okay) {
            qWarning("Datapoint not an expected data type");
            continue;
        }

        qreal x = (width / points) * index;

        qreal percentOfDelta = (dataValue != minValue)? (dataValue - minValue) / (maxValue - minValue): 0.0;
        qreal y = height * percentOfDelta;

        qreal z = -(column() * 0.01);

        glPushName(index);
        glBegin(GL_POINTS);
        if(sizeof(qreal) == sizeof(float)) {
            glVertex3f(x, y, z);
        } else {
            glVertex3d(x, y, z);
        }
        glEnd();
        glPopName();
    }
    glPopName();
}

void LineDataSeries::rebuild()
{
    init();
}
