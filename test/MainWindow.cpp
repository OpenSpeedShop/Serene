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

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(this);

    int columns = 5;
    int rows = 10;

    QStringList headers;
    for(int i = 0; i < columns; ++i) {
        headers.append(QString("Column_%1").arg(i));

        for(int j = 0; j < rows; ++j) {
            QStandardItem *item = new QStandardItem();
            if(i == (columns - 1)) {
                item->setText(QString("Row_%1").arg(j));
            } else {
                item->setData(qrand(), Qt::DisplayRole);
            }
            model->setItem(j, i, item);
        }
    }
    model->setHorizontalHeaderLabels(headers);

    ui->widget->setModel(model);
    ui->widget->updateGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}
