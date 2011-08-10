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

#include "GridLine.h"
#include "GraphWidget.h"
#include "GraphText.h"

#include <QDebug>

namespace Serene {

GridLine::GridLine(QObject *parent) :
    BoundedPrimitive(parent)
{
}

bool GridLine::hasPerspective() const
{
    return m_HasPerspective;
}

void GridLine::setHasPerspective(bool hasPerspective)
{
    m_HasPerspective = hasPerspective;
}


void GridLine::init()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    if(listId() > 0) {
        glDeleteLists(listId(), 1);
        setListId(0);
    }

    setListId(glGenLists(1));
    glNewList(listId(), GL_COMPILE);

    QColor color(Qt::white);
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

    glLineWidth(1);

    /* Cross hairs */
    BoundingCube *boundingCube = this->boundingCube();
    qreal boundingWidth = boundingCube->width();
    qreal boundingHeight = boundingCube->height();
    qreal boundingDepth = boundingCube->depth();

    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(boundingWidth, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, boundingHeight, 0.0);
    if(hasPerspective()) {
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, -boundingDepth);
    }
    glEnd();

    int points = xLabels().count() - 1;
    qreal space = boundingWidth / points;
    glBegin(GL_LINES);
    for(int index = 1; index <= points; ++index) {
        double x = (double)(space * index);
        glVertex3d(x, -1.5, 0.0);
        glVertex3d(x, 1.5, 0.0);
    }
    glEnd();

    points = yLabels().count() - 1;
    space = boundingHeight / points;
    glBegin(GL_LINES);
    for(int index = 1; index <= points; ++index) {
        double y = (double)(space * index);
        glVertex3d(-1.5, y, 0.0);
        glVertex3d(1.5, y, 0.0);
    }
    glEnd();

    if(hasPerspective()) {
        points = zLabels().count() - 1;
        space = boundingHeight / points;
        glBegin(GL_LINES);
        for(int index = 1; index <= points; ++index) {
            double z = (double)(space * index);
            glVertex3d(-1.5, 0.0, z);
            glVertex3d(1.5, 0.0, z);
        }
        glEnd();
    }

    glEndList();

    //! \todo Translate, instead of deleting and recreating the text labels
    qDeleteAll(m_Children);
    m_Children.clear();
    buildTextLabels();

    GraphPrimitive::init();
}


void GridLine::buildTextLabels()
{
    /* Build text labels */
    BoundingCube *boundingCube = this->boundingCube();
    qreal boundingWidth = boundingCube->width();
    qreal boundingHeight = boundingCube->height();
    qreal boundingDepth = boundingCube->depth();
    qreal textScale = 4.0;

    int labelIndex = 0;
    int labelCount = xLabels().count() - 1;
    foreach(QString label, xLabels()) {
        GraphText *graphText = new GraphText(this);
        graphText->setText(label);

        qreal x = ((boundingWidth / labelCount) * labelIndex++) - (textScale / 2.0);

        graphText->setLocation(QVector3D(x, -1.0, 0.0));
        graphText->setOrientation(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 90));
        graphText->setScale(QVector3D(textScale, textScale, 0.0));

        graphText->init();
        m_Children.append(graphText);
    }

    labelIndex = 0;
    labelCount = yLabels().count() - 1;
    foreach(QString label, yLabels()) {
        GraphText *graphText = new GraphText(this);
        graphText->setText(label);

        qreal y = ((boundingHeight / labelCount) * (labelIndex++)) - (textScale / 2.0);

        graphText->setLocation(QVector3D(-(graphText->width() * textScale) - 1.0, y, 0.0));
//        graphText->setOrientation(QQuaternion::fromAxisAndAngle(0.0, 0.0, -1.0, 0));
        graphText->setScale(QVector3D(textScale, textScale, 0.0));

        graphText->init();
        m_Children.append(graphText);
    }

    if(hasPerspective()) {
        labelIndex = 0;
        labelCount = zLabels().count() - 1;
        foreach(QString label, zLabels()) {
            GraphText *graphText = new GraphText(this);
            graphText->setText(label);

            qreal z = ((boundingDepth / labelCount) * (labelIndex++)) - (textScale / 2.0);

            graphText->setLocation(QVector3D(-1.0, 0.0, -z));
            graphText->setOrientation(QQuaternion::fromAxisAndAngle(1.0, 0.0, 0.0, 90));
            graphText->setScale(QVector3D(textScale, textScale, 0.0));

            graphText->init();
            m_Children.append(graphText);
        }
    }

}

QList<QString> GridLine::xLabels() const
{
    return m_XLabels;
}

void GridLine::setXLabels(const QList<QString> &xLabels)
{
    m_XLabels = xLabels;
}

QList<QString> GridLine::yLabels() const
{
    return m_YLabels;
}

void GridLine::setYLabels(const QList<QString> &yLabels)
{
    m_YLabels = yLabels;
}

QList<QString> GridLine::zLabels() const
{
    return m_ZLabels;
}

void GridLine::setZLabels(const QList<QString> &zLabels)
{
    m_ZLabels = zLabels;
}

} // namespace Serene
