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

#include "authorizedevicedialog.h"
#include "ui_authorizedevicedialog.h"



AuthorizeDeviceDialog::AuthorizeDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizeDeviceDialog)
{
    ui->setupUi(this);

    ui->comboBox->addItem(" ");
    //TODO: Check if drive is already authorized.
    DWORD numDrives;
    std::vector<char> usbDrives = UsbDevice::getUSBDrives(&numDrives);
    int i = 0;
    for (std::vector<char>::const_iterator itt = usbDrives.begin(); i < numDrives; std::advance(itt, 4), i++)
    {
        if ((*itt != '\0') && (*itt != 'C'))
        {
            UINT drvFilter = GetDriveTypeA(UsbDevice::ltrtstr(*itt).c_str());
            if ((drvFilter == DRIVE_REMOVABLE) || (drvFilter == DRIVE_FIXED))
            {
                std::string fs;
                UsbDevice::GetVolumeFilesystem(*itt, &fs);
                if ((strcmp(fs.c_str(), "FAT32") == 0) || (strcmp(fs.c_str(), "FAT16") == 0))
                    ui->comboBox->addItem(QString(*itt) + ":\\");
            }
        }
    }
    ui->pushButton->setEnabled(false);
}

AuthorizeDeviceDialog::~AuthorizeDeviceDialog()
{
    delete ui;
}

void AuthorizeDeviceDialog::on_comboBox_activated(const QString &arg1)
{
    if (arg1 == " ")
        return;
    DriveInfo drvInfo;
    if (UsbDevice::getDriveInfo(&drvInfo, arg1.toStdString()))
    {
        ui->label_2->setText(QString("%1   %2").arg("Letter: ").arg(QString(arg1)));
        ui->label_3->setText(QString("%1   %2").arg("Name: ").arg(QString(drvInfo.devName)));
        ui->label_4->setText(QString("%1   %2").arg("Filesystem: ").arg(QString(drvInfo.devFs)));

        ULONGLONG freeSpace, totalSpace;
        if (convToGB(&freeSpace, drvInfo.fSpace) == _GIGABYTE)
            ui->label_5->setText(QString("%1   %2 %3").arg("Free Space: ").arg(QString::number(freeSpace)).arg(QString("GB")));
        else
            ui->label_5->setText(QString("%1   %2 %3").arg("Free Space: ").arg(QString::number(freeSpace)).arg(QString("MB")));
        if (convToGB(&totalSpace, drvInfo.tSpace) == _GIGABYTE)
            ui->label_6->setText(QString("%1   %2 %3").arg("Total Space: ").arg(QString::number(totalSpace)).arg(QString("GB")));
        else
            ui->label_6->setText(QString("%1   %2 %3").arg("Total Space: ").arg(QString::number(totalSpace)).arg(QString("MB")));

        ui->pushButton->setEnabled(true);
    }
}

int AuthorizeDeviceDialog::convToGB(ULONGLONG *new_size, ULONGLONG orig_size)
{
    if ((orig_size >> 20) > 1024)
    {
        *new_size = (orig_size >> 30);
        return _GIGABYTE;
    }
    else
    {
        *new_size = (orig_size >> 20);
        return _MEGABYTE;
    }
}

void AuthorizeDeviceDialog::on_pushButton_clicked()
{
    if (strlen((char*)ui->comboBox->currentText().toStdString().c_str()) > 1)
    {
        AuthDrive drv;
        drv.date = drv.dateAndTime();
        drv.serial = drv.generateRandomString();
        drv.notes = ui->plainTextEdit->toPlainText().toStdString();
        drv.driveName = ui->label_3->text().toStdString();
        drv.driveName.erase(0, 6); //Trim the data from label "Name: "
        drv.driveSize = atoi(ui->label_6->text().toStdString().c_str());
        drv.logEntry();
    }
    else
        QMessageBox::critical(this, "Error", "Error, please select a valid drive letter.");
}
