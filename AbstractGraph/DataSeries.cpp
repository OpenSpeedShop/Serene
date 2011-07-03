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

#include "DataSeries.h"

DataSeries::DataSeries(GraphWidget *parent) :
    GraphPrimitive(parent),
    m_Column(-1)
{
}

void DataSeries::init(int column)
{
    /* IMPLEMENT IN A SUBCLASS; Don't forget to call this base method, though. */

    m_Column = column;
    GraphPrimitive::init();
}

int DataSeries::column()
{
    return m_Column;
}