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
 #ifndef MANAGEDRIVESDIALOG_H
#define MANAGEDRIVESDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QMessageBox>

#include <../../USBNinjaDll/sql.h>
#include <../../USBNinjaDll/paths.h>

namespace Ui {
class ManageDrivesDialog;
}

class ManageDrivesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ManageDrivesDialog(QWidget *parent = 0);
    void refreshData();
    ~ManageDrivesDialog();
    
private slots:
    void on_pushButton_clicked();
    void deleteDeviceHandler();

    void on_pushButton_2_clicked();

private:
    Ui::ManageDrivesDialog *ui;
};

#endif // MANAGEDRIVESDIALOG_H
