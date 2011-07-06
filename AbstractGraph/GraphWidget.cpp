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

#include "GraphWidget.h"
#include <QtOpenGL>

#ifdef QT_DEBUG
#  include <QDebug>
#endif

#ifndef GL_MULTISAMPLE
#  define GL_MULTISAMPLE  0x809D
#endif

GraphWidget::GraphWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

GraphWidget::~GraphWidget()
{
}

QSize GraphWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GraphWidget::sizeHint() const
{
    return QSize(640, 480);
}

bool GraphWidget::is3Dimensional()
{
    return true;
}

void GraphWidget::initializeGL()
{
    qglClearColor(Qt::black);

    m_Camera.setHasPerspective(is3Dimensional());
    m_Camera.setFarPlane(500.0);

    //TODO: Move the view to center and display the entire object
    m_Camera.translateLocation(QVector3D(0.0, 0.0, -15.0));
    m_Camera.translate(QVector3D(12.5, 5.0, 0.0));

    connect(&m_Camera, SIGNAL(viewChanged()), this, SLOT(repaint()));

    init();
}

void GraphWidget::init()
{
    glEnable(GL_CULL_FACE);
}

void GraphWidget::paintGL()
{
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    m_Camera.refreshView();

    paint();
}

void GraphWidget::paint()
{
    foreach(GraphPrimitive *primitive, m_Primitives) {
        primitive->paint();
    }
}


void GraphWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    m_Camera.setAspectRatio((double)width/(double)height);
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    m_LastMousePosition = event->pos();

    event->accept();
    QGLWidget::mousePressEvent(event);
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() != Qt::NoButton) {
        QVector3D oldPos(m_LastMousePosition.x() - (width() / 2.0), m_LastMousePosition.y() - (height() / 2.0), 0.0);
        QVector3D newPos(event->x() - (width() / 2.0), event->y() - (height() / 2.0), 0.0);
        QVector3D delta(oldPos - newPos);

        if(delta.length() != 0.0) {
            if(is3Dimensional() &&
#ifdef Q_OS_DARWIN
                    event->buttons() == Qt::RightButton &&      // Mac hardware doesn't typically have a middle button
#else
                    event->buttons() == Qt::MidButton &&        // Everybody else does
#endif
                    event->modifiers() == Qt::NoModifier) {
                m_Camera.rotateAboutCenter(delta.y(), delta.x(), 0.0);

            } else if(event->buttons() == Qt::MidButton &&
                      event->modifiers() == Qt::ControlModifier) {
                //TODO: Do a direct conversion to projection coordinates, instead of this cludge
                double x = (delta.x() != 0)? delta.x()/36: 0;
                double y = (delta.y() != 0)? -delta.y()/36: 0;
                m_Camera.translate(QVector3D(x, y, 0.0));

            }
        }
    }

    m_LastMousePosition = event->pos();
    QGLWidget::mouseMoveEvent(event);
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    if (event->orientation() == Qt::Vertical &&
            event->modifiers() == Qt::NoModifier) {
        float numSteps = event->delta() / 120.0f;
        if((m_Camera.distance() - 1) < numSteps) {      // Don't get too close to the object
            numSteps = m_Camera.distance() - 1;
        }

        m_Camera.translateLocation(QVector3D(0.0, 0.0, numSteps));
    }

    QGLWidget::wheelEvent(event);
}
