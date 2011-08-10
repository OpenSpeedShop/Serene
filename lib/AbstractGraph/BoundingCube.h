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

#ifndef BOUNDINGCUBE_H
#define BOUNDINGCUBE_H

#include <QObject>
#include <QVector3D>

namespace Serene {

class BoundingCube : public QObject
{
    Q_OBJECT
public:
    explicit BoundingCube(QObject *parent = 0);

    QVector3D position() const { return m_Position; }
    void setPosition(QVector3D position) { m_Position = position; emit positionChanged(); }
    qreal x() const { return m_Position.x(); }
    void setX(qreal x) { m_Position.setX(x); emit positionChanged(); }
    qreal y() const { return m_Position.y(); }
    void setY(qreal y) { m_Position.setY(y); emit positionChanged(); }
    qreal z() const { return m_Position.z(); }
    void setZ(qreal z) { m_Position.setZ(z); emit positionChanged(); }

    QVector3D size() const { return m_Size; }
    void setSize(QVector3D size) { m_Size = size; emit sizeChanged(); }
    qreal width() const { return m_Size.x(); }
    void setWidth(qreal width) { m_Size.setX(width); emit sizeChanged(); }
    qreal height() const { return m_Size.y(); }
    void setHeight(qreal height) { m_Size.setY(height); emit sizeChanged(); }
    qreal depth() const { return m_Size.z(); }
    void setDepth(qreal depth) { m_Size.setZ(depth); emit sizeChanged(); }

    qreal maxValue() const { return m_MaxValue; }
    void setMaxValue(const qreal &maxValue) { m_MaxValue = maxValue; emit scaleChanged(); }

    qreal minValue() const { return m_MinValue; }
    void setMinValue(const qreal &minValue) { m_MinValue = minValue; emit scaleChanged(); }

signals:
    void positionChanged();
    void sizeChanged();
    void scaleChanged();

private:
    QVector3D m_Position;
    QVector3D m_Size;

    qreal m_MaxValue;
    qreal m_MinValue;

};

} // namespace Serene

#endif // BOUNDINGCUBE_H
