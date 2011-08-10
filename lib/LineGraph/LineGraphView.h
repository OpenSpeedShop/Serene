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

#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QAbstractItemView>
#include <QListWidget>
#include "SereneLibrary.h"
#include "LineGraph/LineGraphWidget.h"

namespace Serene {

class SERENE_EXPORT LineGraphView : public QAbstractItemView
{
    Q_OBJECT

public:
    explicit LineGraphView(QWidget *parent = 0);

    void updateGraph();

    /* BEGIN QAbstractItemView interface */
public:
    virtual QRect visualRect(const QModelIndex &index) const;
    virtual void scrollTo(const QModelIndex &index,ScrollHint hint=EnsureVisible);
    virtual QModelIndex indexAt(const QPoint &point) const;

    virtual void setModel(QAbstractItemModel *model);

protected:
    virtual QModelIndex moveCursor(CursorAction cursorAction,Qt::KeyboardModifiers modifiers);
    virtual int horizontalOffset() const;
    virtual int verticalOffset() const;
    virtual bool isIndexHidden(const QModelIndex &index) const;
    virtual void setSelection(const QRect &rect,QItemSelectionModel::SelectionFlags command);
    virtual QRegion visualRegionForSelection(const QItemSelection &selection) const;

    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    /* END QAbstractItemView interface */

    virtual bool event(QEvent *event);
    virtual bool helpEvent(QHelpEvent * event);

private:
    LineGraphWidget *m_LineGraphWidget;
    QListWidget *m_ListWidget;

};

} // namespace Serene

#endif // GRAPHVIEW_H
