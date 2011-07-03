/*!
   \file
   \author Dane Gardner <dane.gardner@gmail.com>
   \version

   \section LICENSE
   This file is part of the Open|SpeedShop Graphical User Interface
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
    QGLWidget(parent),
    m_Rotation(0.0,0.0,0.0),
    m_Translation(-12.5,-5.0,-20.0),
    m_Scale(1.0,1.0,1.0)
{
}

GraphWidget::~GraphWidget()
{
}

QAbstractItemModel *GraphWidget::model()
{
    return m_Model;
}

void GraphWidget::setModel(QAbstractItemModel *model)
{
    m_Model = model;
    initializeGL();
}

QSize GraphWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GraphWidget::sizeHint() const
{
    return QSize(640, 480);
}

void GraphWidget::initializeGL()
{
    qglClearColor(Qt::black);
    init();
}

void GraphWidget::init()
{
}


void GraphWidget::paintGL()
{
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    QVector3D scale = this->scale();
    glScalef(scale.x(), scale.y(), scale.z());

    QVector3D translation = this->translation();
    glTranslatef(0.0f, 0.0f, translation.z());

    QVector3D rotation = this->rotation();
    glRotatef(rotation.x() / 16.0, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y() / 16.0, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z() / 16.0, 0.0f, 0.0f, 1.0f);

    glTranslatef(translation.x(), translation.y(), 0.0);

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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (double)width/(double)height, 0.1, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if(!is3Dimensional()) return;

    m_LastMousePosition = event->pos();

    event->accept();
    QGLWidget::mousePressEvent(event);
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!is3Dimensional()) return;

    int dx = event->x() - m_LastMousePosition.x();
    int dy = event->y() - m_LastMousePosition.y();

#ifdef Q_OS_DARWIN  // Mac hardware doesn't typically have a middle button
    if(event->buttons() & Qt::RightButton) {
#else
    if(event->buttons() & Qt::MidButton) {
#endif
        if(event->modifiers() == Qt::NoModifier) {
            QVector3D rotation = this->rotation();
            rotation.setX(rotation.x() + 8 * dy);
            rotation.setY(rotation.y() + 8 * dx);
            setRotation(rotation);

        } else if(event->modifiers() == Qt::ControlModifier) {
            //TODO: Do a "real" translation related to the view area
            QVector3D translation = this->translation();
            translation.setX(translation.x() + dx*(-translation.z()/16) / 32.0);
            translation.setY(translation.y() - dy*(-translation.z()/16) / 32.0);
            setTranslation(translation);

        }
    }

    m_LastMousePosition = event->pos();
    QGLWidget::mouseMoveEvent(event);
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    if(!is3Dimensional()) return;

    float numDegrees = event->delta() / 8.0f;
    float numSteps = numDegrees / 15.0f;

    if (event->orientation() == Qt::Vertical) {
        if(event->modifiers() == Qt::NoModifier) {
            QVector3D translation = this->translation();
            translation.setZ(translation.z() + numSteps);
            setTranslation(translation);
        }
    }

    QGLWidget::wheelEvent(event);
}

QVector3D GraphWidget::rotation() const
{
    return m_Rotation;
}


void GraphWidget::setRotation(const QVector3D &rotation)
{
    float angle = rotation.x();
    while(angle < 0) { angle += 360 * 16; }
    while(angle > 360 * 16) { angle -= 360 * 16; }
    m_Rotation.setX(angle);

    angle = rotation.y();
    while(angle < 0) { angle += 360 * 16; }
    while(angle > 360 * 16) { angle -= 360 * 16; }
    m_Rotation.setY(angle);

    angle = rotation.z();
    while(angle < 0) { angle += 360 * 16; }
    while(angle > 360 * 16) { angle -= 360 * 16; }
    m_Rotation.setZ(angle);

    repaint();
}

QVector3D GraphWidget::translation() const
{
    return m_Translation;
}

void GraphWidget::setTranslation(const QVector3D &translation)
{
    m_Translation = translation;
    repaint();
}

QVector3D GraphWidget::scale() const
{
    return m_Scale;
}

void GraphWidget::setScale(const QVector3D &scale)
{
    m_Scale = scale;
    repaint();
}
