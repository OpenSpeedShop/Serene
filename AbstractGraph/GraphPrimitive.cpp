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

GraphPrimitive::GraphPrimitive(GraphWidget *parent) :
    QObject(parent),
    m_Initialized(false),
    m_ListId(0)
{
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

    glCallList(listId());
}

GraphWidget *GraphPrimitive::parentGraphWidget()
{
    return qobject_cast<GraphWidget *>(parent());
}

bool GraphPrimitive::isValid()
{
    return m_Initialized;
}

void GraphPrimitive::setListId(GLuint listId)
{
    m_ListId = listId;
}

GLuint GraphPrimitive::listId()
{
    return m_ListId;
}

