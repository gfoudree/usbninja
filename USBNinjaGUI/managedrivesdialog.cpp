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
 
#include "managedrivesdialog.h"
#include "ui_managedrivesdialog.h"

ManageDrivesDialog::ManageDrivesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageDrivesDialog)
{
    ui->setupUi(this);

    QStringList columnTitles;
    columnTitles << "ID" << "Date Authorized" << "USBNinja Serial" << "Name" << "Size" << "Notes";
    ui->treeWidget->setHeaderLabels(columnTitles);
    ui->treeWidget->setColumnWidth(0, 40);

    refreshData();

    QMenu *contextMenu = new QMenu(ui->treeWidget);
    ui->treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *deleteDrive = new QAction("Delete Device", contextMenu);
    ui->treeWidget->addAction(deleteDrive);

    connect(deleteDrive, SIGNAL(triggered()), this, SLOT(deleteDeviceHandler()));
}

void ManageDrivesDialog::refreshData()
{
    ui->treeWidget->clear();
    std::vector<authedDrive> authedDrv;
    Sql sql;
    sql.dbConnect("C:\\users\\grant\\desktop\\log.db");
    sql.queryAuthedDrives(&authedDrv);
    sql.dbDisconnect();

    for (int i = authedDrv.size(), element = 0; i != 0; i--, element++)
    {
        QStringList data;
        data << QString::number(i) << authedDrv.at(element).dateAuthorized.c_str();
        data << authedDrv.at(element).serial.c_str() << authedDrv.at(element).driveName.c_str();
        data << QString::number(authedDrv.at(element).driveSize) << authedDrv.at(element).notes.c_str();

        QTreeWidgetItem *itm = new QTreeWidgetItem(data);
        ui->treeWidget->insertTopLevelItem(0, itm);
    }
    ui->treeWidget->resizeColumnToContents(2);
}

ManageDrivesDialog::~ManageDrivesDialog()
{
    delete ui;
}

void ManageDrivesDialog::on_pushButton_clicked()
{
    done(0);
}

void ManageDrivesDialog::deleteDeviceHandler()
{
    QTreeWidgetItem *itm = ui->treeWidget->currentItem();
    int id = atoi(itm->text(0).toStdString().c_str());

    char *warningMsg = (char*)malloc(1024);
    sprintf(warningMsg, "Are you sure you want to delete %s authorized on %s?" \
            " The drive will no longer be able to access this computer unless reauthorized!",
            itm->text(3).toStdString().c_str(), itm->text(1).toStdString().c_str());

    int choice = QMessageBox::warning(this, "Warning!", QString(warningMsg),
                                      QMessageBox::Yes | QMessageBox::No);

    if (choice == QMessageBox::Yes)
    {
        char statement[50];
        sprintf(statement, "DELETE FROM authDrives WHERE id=\'%d\';", id);

        Sql sql("C:\\users\\grant\\desktop\\log.db");
        sql.dbExecSql(statement);
        sql.dbDisconnect();
    }
    refreshData();
    free(warningMsg);
}
