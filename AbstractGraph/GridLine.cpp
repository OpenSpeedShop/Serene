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

GridLine::GridLine(GraphWidget *parent) :
    GraphPrimitive(parent)
{
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
    glBegin(GL_LINES);
    glVertex3d(-1.0f, 0.0f, 0.0f);
    glVertex3d(25.0f, 0.0f, 0.0f);
    glVertex3d(0.0f, -1.0f, 0.0f);
    glVertex3d(0.0f, 10.0f, 0.0f);
    glVertex3d(0.0f, 0.0f, -5.0f);
    glVertex3d(0.0f, 0.0f, 1.0f);
    glEnd();

    {
        int points = 100;
        qreal space = 25.0/points;
        glBegin(GL_LINES);
        for(int index = 1; index < points+1; ++index) {
            float x = (float)(space * (index));
            float y = 0.0;
            if((index % 2) == 0) {
                if((index % 10) == 0) {
                    y = 0.25;
                } else {
                    y = 0.1;
                }
            }
            glVertex3d(x, -y, 0.0);
            glVertex3d(x, y, 0.0);
        }
        glEnd();
    }

    {
        int points = 100;
        qreal space = 10.0/points;
        glBegin(GL_LINES);
        for(int index = 1; index < points+1; ++index) {
            float x = 0.0;
            if((index % 5) == 0) {
                if((index % 10) == 0) {
                    x = 0.25;
                } else {
                    x = 0.1;
                }
            }
            float y = (float)(space * (index));
            glVertex3d(-x, y, 0.0);
            glVertex3d(x, y, 0.0);
        }
        glEnd();
    }


    /* Box */
//    // Bottom square
//    glBegin(GL_LINE_LOOP);
//    glVertex3f(0.0f,0.0f,0.0f);
//    glVertex3f(25.0f,0.0f,0.0f);
//    glVertex3f(25.0f,0.0f,-10.0f);
//    glVertex3f(0.0f,0.0f,-10.0f);
//    glEnd();

//    // Top square
//    glBegin(GL_LINE_LOOP);
//    glVertex3f(0.0f,10.0f,0.0f);
//    glVertex3f(25.0f,10.0f,0.0f);
//    glVertex3f(25.0f,10.0f,-10.0f);
//    glVertex3f(0.0f,10.0f,-10.0f);
//    glEnd();

//    // Lines connecting the top and bottom corners
//    glBegin(GL_LINES);
//    glVertex3f(0.0f,10.0f,0.0f);
//    glVertex3f(0.0f,0.0f,0.0f);
//    glVertex3f(25.0f,10.0f,0.0f);
//    glVertex3f(25.0f,0.0f,0.0f);
//    glVertex3f(25.0f,10.0f,-10.0f);
//    glVertex3f(25.0f,0.0f,-10.0f);
//    glVertex3f(0.0f,10.0f,-10.0f);
//    glVertex3f(0.0f,0.0f,-10.0f);
//    glEnd();

    glEndList();

    GraphPrimitive::init();
}

