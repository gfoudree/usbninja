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
#include <QMainWindow>
#include <QFileDialog>
#include <windows.h>
#include <../../USBNinjaDll/sql.h>
#include <../../USBNinjaDll/errorlog.h>
#include <../../USBNinjaDll/service.h>
#include <../../USBNinjaDll/paths.h>

#include "csvexport.h"
#include "aboutdialog.h"
#include "managedrivesdialog.h"
#include "graphdialog.h"
#include "logviewdialog.h"
#include "settingsdialog.h"

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
    void on_actionUnauthorize_All_Devices_triggered();
    void on_actionGraph_Data_triggered();

    void expandAllHandler();
    void collapseAllHandler();

    void on_actionExport_to_CSV_triggered();

    void on_actionReload_Log_triggered();

    void on_actionView_Log_triggered();

    void on_actionStart_Monitoring_triggered();

    void on_actionStop_Monitoring_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
