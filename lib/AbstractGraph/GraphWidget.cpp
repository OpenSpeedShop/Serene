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

namespace Serene {

GraphWidget::GraphWidget(QWidget *parent) :
    QGLWidget(parent),
    m_BoundingCube()
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

    // Move the view to center and display the entire object
    m_Camera.translateLocation(QVector3D(0.0, 0.0, -100.0));
    QVector3D cameraLocation = m_BoundingCube.size();
    cameraLocation.setX(cameraLocation.x() / 2);
    cameraLocation.setY(cameraLocation.y() / 2);
    cameraLocation.setZ(0.0);
    cameraLocation += m_BoundingCube.position();
    m_Camera.translate(cameraLocation);

    connect(&m_Camera, SIGNAL(viewChanged()), this, SLOT(repaint()));

    init();
}

void GraphWidget::init()
{
    glEnable(GL_CULL_FACE);


    /* Enable anti-aliasing for lines and points */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


    m_GridLine.setBoundingCube(&m_BoundingCube);
    m_GridLine.setHasPerspective(is3Dimensional());
    m_GridLine.init();

    if(!m_Primitives.contains(&m_GridLine)) {
        m_Primitives.append(&m_GridLine);
    }

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
    double aspectRatio = (double)width / (double)height;

    QVector3D size(100.0, 100.0 / aspectRatio, 100.0);
    m_BoundingCube.setSize(size);

    m_Camera.setAspectRatio(aspectRatio);
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
                m_Camera.rotateAboutCenter(delta.x(), delta.y(), 0.0);

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
    if (event->orientation() == Qt::Vertical && event->modifiers() == Qt::NoModifier) {
        float numSteps = event->delta() / 120.0f;
        if((m_Camera.distance() - 1) < numSteps) {      // Don't get too close to the object
            numSteps = m_Camera.distance() - 1;
        }
        m_Camera.translateLocation(QVector3D(0.0, 0.0, numSteps));
    }

    QGLWidget::wheelEvent(event);
}

QPair<qint32, qint32> GraphWidget::itemAt(QPoint position)
{
    // Set up the selection buffer
    int count = 512;
    GLuint buffer[count];
    for(int i=0; i<count; ++i) buffer[i] = 0;
    glSelectBuffer(count, buffer);

    // Initialize the names and render mode
    glInitNames();
    glRenderMode(GL_SELECT);

    // Get the current projection matrix
    GLdouble projectionMatrix[16];
    glGetDoublev( GL_PROJECTION_MATRIX, projectionMatrix );

    // Get the current viewport
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Preserve the projection matrix (we don't calculate it every frame)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    // Set up a projection several pixels wide around the point
    glLoadIdentity();
    gluPickMatrix((GLdouble)position.x(), (GLdouble)(viewport[3] - position.y()), 5.0, 5.0, viewport);
    glMultMatrixd(projectionMatrix);

    // Do the pick render
    glMatrixMode(GL_MODELVIEW);
    foreach(GraphPrimitive *primitive, m_Primitives) {
        primitive->pick();
    }

    // Bring back the original projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Get the number of hits for the location
    glFlush();
    GLint hits = glRenderMode(GL_RENDER);

//    // Output the debugging information for the returned buffer
//    QString bufferText("{");
//    for(int i = 0; i < 128; ++i) {
//        bufferText.append(QString("%1;").arg(buffer[i]));
//    }
//    bufferText.append("}");
//    qDebug() << bufferText;

    // Find the nearest object and return it's name
    GLuint lastZ = 0xFFFFFFFF;
    GLuint column = 0xFFFFFFFF;
    GLuint row = 0xFFFFFFFF;
    GLuint *ptr = buffer;
    for(qint32 i = 0; i < hits; ++i) {
        GLuint names = *ptr;
        ptr++;
        GLuint nearZ = *ptr;
        ptr += 2;

        if(nearZ <= lastZ) {
            lastZ = nearZ;
            column = row = 0xFFFFFFFF;
            for(quint32 j = 0; j < names; ++j) {
                if(j == 0) {
                    column = *ptr;
                } else {
                    row = *ptr;
                }
                ++ptr;
            }
        } else {
            ptr += names;
        }
    }

    return QPair<qint32, qint32>((qint32)((column == 0xFFFFFFFF)? -1: column), (qint32)((row == 0xFFFFFFFF)? -1: row));
}

} // namespace Serene
