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

#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <nightcharts.h>

#include <../../USBNinjaDll/sql.h>

namespace Ui {
class GraphDialog;
}

class GraphDialog : public QDialog
{
    Q_OBJECT
    
public:
    int acceptedDrives, rejectedDrives;
    explicit GraphDialog(QWidget *parent = 0);
    ~GraphDialog();
    
private:
    int accepted, denied, total;
    Ui::GraphDialog *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // GRAPHDIALOG_H
