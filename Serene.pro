# This file is part of the Serene 3D Graphing Library
# Copyright (C) 2010-2011 Argo Navis Technologies, LLC
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

QT           += core gui opengl

TARGET        = OpenGL

TEMPLATE      = app

SOURCES      += main.cpp\
                MainWindow.cpp \
                GraphView.cpp \
                AbstractGraph/GridLine.cpp \
                AbstractGraph/DataSeries.cpp \
                AbstractGraph/GraphPrimitive.cpp \
                Graph2D/GraphWidget2D.cpp \
                Graph3D/GraphWidget3D.cpp \
                LineGraph/LineDataSeries.cpp \
                LineGraph/LineGraphWidget.cpp \
    AbstractGraph/Camera.cpp \
    AbstractGraph/GraphText.cpp \
    Graph2D/GridLine2D.cpp \
    AbstractGraph/GraphWidget.cpp \
    AbstractGraph/BoundingCube.cpp \
    AbstractGraph/BoundedPrimitive.cpp

HEADERS      += MainWindow.h \
                GraphView.h \
                AbstractGraph/GridLine.h \
                AbstractGraph/DataSeries.h \
                AbstractGraph/GraphPrimitive.h \
                Graph2D/GraphWidget2D.h \
                Graph3D/GraphWidget3D.h \
                LineGraph/LineDataSeries.h \
                LineGraph/LineGraphWidget.h \
    AbstractGraph/Camera.h \
    AbstractGraph/GraphText.h \
    Graph2D/GridLine2D.h \
    AbstractGraph/GraphWidget.h \
    AbstractGraph/BoundingCube.h \
    AbstractGraph/BoundedPrimitive.h

FORMS        += MainWindow.ui

OTHER_FILES  += README \
                LICENSE \
                COPYRIGHT
