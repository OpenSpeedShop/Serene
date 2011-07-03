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
#include <QAbstractItemModel>
#include "GraphPrimitive.h"

class GraphWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    QAbstractItemModel *model();
    void setModel(QAbstractItemModel *model);

    QVector3D rotation() const;
    void setRotation(const QVector3D &rotation);
    QVector3D translation()const;
    void setTranslation(const QVector3D &translation);
    QVector3D scale() const;
    void setScale(const QVector3D &scale);

    virtual bool is3Dimensional() { return true; }

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *);

    virtual void init();
    virtual void paint();

    QList<GraphPrimitive *> m_Primitives;

private:
    QAbstractItemModel *m_Model;

    QVector3D m_Rotation;
    QVector3D m_Translation;
    QVector3D m_Scale;
    QPoint m_LastMousePosition;

};

#endif // GLWIDGET_H
