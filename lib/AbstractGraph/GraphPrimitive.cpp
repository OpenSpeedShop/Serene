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

#include "GraphPrimitive.h"
#include "GraphWidget.h"

namespace Serene {

GraphPrimitive::GraphPrimitive(QObject *parent) :
    QObject(parent),
    m_Initialized(false),
    m_ListId(0),
    m_Orientation(),
    m_Location(),
    m_Scale(1.0,1.0,1.0)
{
}

GraphPrimitive::~GraphPrimitive()
{
    if(m_ListId) {
        glDeleteLists(m_ListId, 1);
        m_ListId = 0;
    }
}

void GraphPrimitive::init()
{
    /* IMPLEMENT IN A SUBCLASS; Don't forget to call this base method, though. */

    m_Initialized = true;
}

void GraphPrimitive::paint()
{
    if(!isValid()) {
        qWarning("GraphPrimitive object painted before initialized.");
        init();
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    QMatrix4x4 matrix;
    matrix.translate(location());
    matrix.rotate(orientation());
    matrix.scale(scale());
    if(sizeof(qreal) == sizeof(GLdouble)) {
        glMultMatrixd((GLdouble *)matrix.constData());
    } else {
        glMultMatrixf((GLfloat *)matrix.constData());
    }

    glCallList(listId());

    foreach(GraphPrimitive *primitive, m_Children) {
        primitive->paint();
    }

    glPopMatrix();
}

void GraphPrimitive::pick()
{
    if(!isValid()) {
        qWarning("GraphPrimitive object picked before initialized.");
        init();
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    QMatrix4x4 matrix;
    matrix.translate(location());
    matrix.rotate(orientation());
    matrix.scale(scale());
    if(sizeof(qreal) == sizeof(GLdouble)) {
        glMultMatrixd((GLdouble *)matrix.constData());
    } else {
        glMultMatrixf((GLfloat *)matrix.constData());
    }

    pickRender();

    foreach(GraphPrimitive *primitive, m_Children) {
        primitive->pickRender();
    }

    glPopMatrix();
}

void GraphPrimitive::pickRender()
{
    //TODO: re-implement for pickable items
}

bool GraphPrimitive::isValid()
{
    return m_Initialized;
}

void GraphPrimitive::setListId(GLuint listId)
{
    if(m_ListId) {
        glDeleteLists(m_ListId, 1);
    }

    m_ListId = listId;
}

GLuint GraphPrimitive::listId()
{
    return m_ListId;
}

const QQuaternion &GraphPrimitive::orientation() const
{
    return m_Orientation;
}

void GraphPrimitive::setOrientation(const QQuaternion &orientation)
{
    m_Orientation = orientation;
}

const QVector3D &GraphPrimitive::location() const
{
    return m_Location;
}

void GraphPrimitive::setLocation(const QVector3D &location)
{
    m_Location = location;
}

const QVector3D &GraphPrimitive::scale() const
{
    return m_Scale;
}

void GraphPrimitive::setScale(const QVector3D &scale)
{
    m_Scale = scale;
}

} // namespace Serene
