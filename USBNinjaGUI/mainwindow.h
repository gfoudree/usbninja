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
 
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../../USBNinjaDll/sql.h>

#include "aboutdialog.h"
#include "managedrivesdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadData();
    void clearData();
    
private slots:
    void on_actionExit_triggered();
    void on_actionClear_Log_triggered();
    void on_actionAbout_triggered();
    void on_actionManage_Devices_triggered();

    void expandAllHandler();
    void collapseAllHandler();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
