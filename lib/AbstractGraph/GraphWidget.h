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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include "AbstractGraph/GridLine.h"
#include "GraphPrimitive.h"
#include "Camera.h"
#include "BoundingCube.h"

namespace Serene {

class GraphWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    virtual bool is3Dimensional();

    virtual QPair<qint32, qint32> itemAt(QPoint position);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);


    virtual void init();
    virtual void paint();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *);

    Camera m_Camera;
    BoundingCube m_BoundingCube;
    GridLine m_GridLine;
    QList<GraphPrimitive *> m_Primitives;

private:
    QPoint m_LastMousePosition;

};

} // namespace Serene

#endif // GLWIDGET_H
