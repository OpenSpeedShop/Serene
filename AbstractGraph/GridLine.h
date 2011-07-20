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

#ifndef GRIDLINE_H
#define GRIDLINE_H

#include "BoundedPrimitive.h"

class GraphWidget;

class GridLine : public BoundedPrimitive
{
    Q_OBJECT
public:
    explicit GridLine(QObject *parent = 0);

    virtual bool is3Dimensional();
    void init();

    void buildTextLabels();
    QList<QString> xLabels() const;
    void setXLabels(const QList<QString> &xLabels);
    QList<QString> yLabels() const;
    void setYLabels(const QList<QString> &yLabels);
    QList<QString> zLabels() const;
    void setZLabels(const QList<QString> &zLabels);


private:
    QList<QString> m_XLabels;
    QList<QString> m_YLabels;
    QList<QString> m_ZLabels;
};

#endif // GRIDLINE_H
