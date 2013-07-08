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
#ifndef LOGVIEWDIALOG_H
#define LOGVIEWDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QMessageBox>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>

#include <../../USBNinjaDll/paths.h>

struct logFileFormat;

namespace Ui {
class LogviewDialog;
}

class LogviewDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LogviewDialog(QWidget *parent = 0);
    ~LogviewDialog();
    
private:
    void refreshUI();
    bool parseLogFile(std::vector<logFileFormat> &data,  char *filePath);
    Ui::LogviewDialog *ui;

private slots:
    void onClearLogfile();
};


struct logFileFormat
{
    std::string date;
    std::string urgency;
    std::string info;
};

#endif // LOGVIEWDIALOG_H
