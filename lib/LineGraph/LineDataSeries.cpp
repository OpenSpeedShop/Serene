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

namespace Serene {

LineDataSeries::LineDataSeries(QObject *parent) :
    DataSeries(parent)
{
}

void LineDataSeries::init()
{
    /* If it hasn't already been initialized, connect the necessary slots */
    if(!isValid()) {
        connect(this, SIGNAL(columnChanged()), this, SLOT(rebuild()));
        connect(this, SIGNAL(dataChanged()), this, SLOT(rebuild()));
        connect(this, SIGNAL(colorChanged()), this, SLOT(rebuild()));
    }

    /* Delete any previous lists */
    if(listId() > 0) {
        glDeleteLists(listId(), 1);
        setListId(0);
    }

    int pointCount = data().count() - 1;
    qreal width = boundingCube()->width();
    qreal height = boundingCube()->height();

    qreal maxValue = boundingCube()->maxValue();
    qreal minValue = boundingCube()->minValue();

    QList<QVector3D> points;
    foreach(QVariant dataPoint, data()) {
        bool okay = false;
        qreal dataValue = dataPoint.toReal(&okay);

        if(!okay) {
            dataValue = (qreal(dataPoint.toLongLong(&okay)));
        }

        if(!okay) {
            qWarning("Datapoint not an expected data type");
            continue;
        }

        qreal x = (width / pointCount) * points.count();

        qreal percentOfDelta = (dataValue != minValue)? (dataValue - minValue) / (maxValue - minValue): 0.0;
        qreal y = height * percentOfDelta;

        qreal z = -(column() * 0.01);

        QVector3D point(x,y,z);
        points.append(point);
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    setListId(glGenLists(1));
    glNewList(listId(), GL_COMPILE);

    QColor color = this->color();
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

    /* Draw the lines */
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    foreach(QVector3D point, points) {
        glVertex3d(point.x(), point.y(), point.z());
    }
    glEnd();

    /* Draw the points */
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    foreach(QVector3D point, points) {
        glVertex3d(point.x(), point.y(), point.z());
    }
    glEnd();

    glEndList();

    DataSeries::init();
}

void LineDataSeries::pickRender()
{
    int pointCount = data().count() - 1;
    qreal width = boundingCube()->width();
    qreal height = boundingCube()->height();

    qreal maxValue = boundingCube()->maxValue();
    qreal minValue = boundingCube()->minValue();

    QList<QVector3D> points;
    foreach(QVariant dataPoint, data()) {
        bool okay = false;
        qreal dataValue = dataPoint.toReal(&okay);

        if(!okay) {
            dataValue = (qreal(dataPoint.toLongLong(&okay)));
        }

        if(!okay) {
            qWarning("Datapoint not an expected data type");
            continue;
        }

        qreal x = (width / pointCount) * points.count();

        qreal percentOfDelta = (dataValue != minValue)? (dataValue - minValue) / (maxValue - minValue): 0.0;
        qreal y = height * percentOfDelta;

        qreal z = -(column() * 0.01);

        QVector3D point(x,y,z);
        points.append(point);
    }

    glPushName(column());
    glBegin(GL_LINE_STRIP);
    foreach(QVector3D point, points) {
        glVertex3d(point.x(), point.y(), point.z());
    }
    glEnd();

    int index = 0;
    glPointSize(7.5f);
    foreach(QVector3D point, points) {
        glPushName(index++);
        glBegin(GL_POINTS);
        glVertex3d(point.x(), point.y(), point.z());
        glEnd();
        glPopName();
    }
    glPopName();
}

void LineDataSeries::rebuild()
{
    init();
}

} // namespace Serene
