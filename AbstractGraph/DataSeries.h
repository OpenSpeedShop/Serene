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

#ifndef DATASERIES_H
#define DATASERIES_H

#include <QObject>
#include <QtOpenGL>
#include "BoundedPrimitive.h"

class DataSeries : public BoundedPrimitive
{
    Q_OBJECT
public:
    explicit DataSeries(QObject *parent = 0);

    virtual void init();

    virtual int column();
    virtual void setColumn(int column);

    QList<QVariant> data() const;
    void setData(const QList<QVariant> &data);

    QColor color() const;
    void setColor(const QColor &color);

    void randomizeData(int points = 100);

signals:
    void dataChanged();
    void colorChanged();
    void columnChanged();

private:
    int m_Column;
    QColor m_Color;
    QList<QVariant> m_Data;

};

#endif // DATASERIES_H
