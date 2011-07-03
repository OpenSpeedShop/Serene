#-------------------------------------------------
#
# Project created by QtCreator 2011-06-28T14:58:53
#
#-------------------------------------------------

QT       += core gui opengl

TARGET    = OpenGL
TEMPLATE  = app

SOURCES  += main.cpp\
            MainWindow.cpp \
            AbstractGraph/GridLine.cpp \
            AbstractGraph/GraphWidget.cpp \
            AbstractGraph/DataSeries.cpp \
            GraphView.cpp \
            AbstractGraph/GraphPrimitive.cpp \
            LineGraph/LineDataSeries.cpp \
            LineGraph/LineGraphWidget.cpp \
            Graph2D/GraphWidget2D.cpp \
            Graph3D/GraphWidget3D.cpp

HEADERS  += MainWindow.h \
            AbstractGraph/GridLine.h \
            AbstractGraph/GraphWidget.h \
            AbstractGraph/DataSeries.h \
            GraphView.h \
            AbstractGraph/GraphPrimitive.h \
            LineGraph/LineDataSeries.h \
            LineGraph/LineGraphWidget.h \
            Graph2D/GraphWidget2D.h \
            Graph3D/GraphWidget3D.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    README.txt
