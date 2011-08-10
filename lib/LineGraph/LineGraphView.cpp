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

#include "LineGraphView.h"

#include <QDebug>

namespace Serene {

LineGraphView::LineGraphView(QWidget *parent) :
    QAbstractItemView(parent),
    m_LineGraphWidget(NULL),
    m_ListWidget(NULL)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setHandleWidth(1);
    layout->addWidget(splitter);

    m_LineGraphWidget = new LineGraphWidget(this);
    splitter->addWidget(m_LineGraphWidget);

    m_ListWidget = new QListWidget(this);
    splitter->addWidget(m_ListWidget);
}

QRect LineGraphView::visualRect(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return(QRect());
}

void LineGraphView::scrollTo(const QModelIndex &index,ScrollHint hint)
{
    Q_UNUSED(index)
    Q_UNUSED(hint)
}

QModelIndex LineGraphView::indexAt(const QPoint &point) const
{
    Q_UNUSED(point)
    qDebug() << point;
    return(QModelIndex());
}

QModelIndex LineGraphView::moveCursor(CursorAction cursorAction,Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(cursorAction)
    Q_UNUSED(modifiers)
    return(QModelIndex());
}

int LineGraphView::horizontalOffset() const
{
    return 0;
}

int LineGraphView::verticalOffset() const
{
    return 0;
}

bool LineGraphView::isIndexHidden(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return false;
}

void LineGraphView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    Q_UNUSED(rect)
    Q_UNUSED(command)
}

QRegion LineGraphView::visualRegionForSelection(const QItemSelection &selection) const
{
    Q_UNUSED(selection)
    return(QRegion());
}

void LineGraphView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight);
    updateGraph();
}

void LineGraphView::setModel(QAbstractItemModel *model)
{
    QAbstractItemView::setModel(model);
    updateGraph();
}


void LineGraphView::updateGraph()
{
    qDeleteAll(*m_LineGraphWidget->lineSeries());
    m_LineGraphWidget->lineSeries()->clear();
    m_ListWidget->clear();

    QAbstractItemModel *model = this->model();
    int columnCount = model->columnCount();
    for(int i=0; i < columnCount; ++i) {
        if(i == (columnCount - 1)) {
            QList<QString> titles;
            for(int j=0; j < model->rowCount(); ++j) {
                QModelIndex index = model->index(j, i);
                titles.append(index.data().toString());
            }
            m_LineGraphWidget->setXLabels(titles);
        } else {
            QList<QVariant> data;
            for(int j=0; j < model->rowCount(); ++j) {
                QModelIndex index = model->index(j, i);
                data.append(index.data());
            }
            m_LineGraphWidget->addColumn(data);

            QListWidgetItem *item = new QListWidgetItem();
            item->setText(model->headerData(i, Qt::Horizontal).toString());
            item->setData(Qt::DecorationRole, QColor((Qt::GlobalColor)(Qt::red + m_ListWidget->count())));
            m_ListWidget->addItem(item);
        }
    }
}


bool LineGraphView::event(QEvent *event)
{
    if(event->type() == QEvent::ToolTip) {
        return helpEvent((QHelpEvent *)event);
    } else {
        return QAbstractItemView::event(event);
    }
}

bool LineGraphView::helpEvent(QHelpEvent * event)
{
    if(event != NULL) {
        QPoint position = event->pos();
        position -= m_LineGraphWidget->pos();   // Translate the event position to the child widget
        if(m_LineGraphWidget->rect().contains(position)) {
            QPair<qint32,qint32> dataCell = m_LineGraphWidget->itemAt(position);

            if(dataCell.first >= 0 && dataCell.second >= 0) {
                QAbstractItemModel *model = this->model();
                QString toolTip = model->index(dataCell.second, dataCell.first).data().toString();
                QToolTip::showText(event->globalPos(), toolTip, this);

            } else if(dataCell.first >= 0 && dataCell.second < 0) {
                QAbstractItemModel *model = this->model();
                QString toolTip = model->headerData(dataCell.first, Qt::Horizontal).toString();
                QToolTip::showText(event->globalPos(), toolTip, this);

            } else {
                QToolTip::hideText();

            }
            event->accept();
            return true;
        }
    }

    return QAbstractItemView::event(event);
}

} // namespace Serene
