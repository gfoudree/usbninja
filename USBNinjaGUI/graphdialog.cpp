/*
 * Copyright (C) by Grant Foudree <grant907@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "graphdialog.h"
#include "ui_graphdialog.h"

GraphDialog::GraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog)
{
    ui->setupUi(this);
}

GraphDialog::~GraphDialog()
{
    delete ui;
}

void GraphDialog::paintEvent(QPaintEvent *event)
{
    int accepted, denied, total;

    Sql sql;
    sql.dbConnect(LOG_FILE);
    accepted = sql.authorizedDrives();
    denied = sql.deniedDrives();
    total = accepted + denied;

    sql.dbDisconnect();

    QWidget::paintEvent(event);
    QPainter painter;
    painter.begin(this);

    Nightcharts pieChart;
    pieChart.setType(Nightcharts::Dpie);
    pieChart.setCords(150, 50, this->width()/2, this->height()/2);
    pieChart.setLegendType(Nightcharts::Round);
    pieChart.addPiece("Accepted", Qt::green, (double)accepted / total *100);
    pieChart.addPiece("Rejected", Qt::red, (double)denied / total *100);
    pieChart.setShadows(false);
    pieChart.draw(&painter);
    pieChart.drawLegend(&painter);


}
