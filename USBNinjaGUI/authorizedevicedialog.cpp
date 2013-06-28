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
        /* Signature:
         *
         * NINJA(serial)(crc32)
         */

        /* Get drive letter */
        char drvLtr;
        std::string drvLtrStr = ui->comboBox->currentText().toStdString();
        drvLtr = drvLtrStr.at(0);

        /* Query drive information so we can log it... */
        DriveInfoS drvInfoS;
        UsbDevice::GetVolumeSize(drvLtr, (unsigned int *)&drvInfoS.diskSize);
        UsbDevice::GetVolumeLabel(drvLtr, &drvInfoS.driveName);
        UsbDevice::GetVolumeFilesystem(drvLtr, &drvInfoS.driveFilesystem);

        /* Setup buffer to write to BPB of device */
        char *buf;
        bool isFat32;
        if (drvInfoS.driveFilesystem.find("FAT32") != 0)
        {
            /* Device is FAT32 */
            buf = (char*)malloc(FAT32_BPB_BOOTCODE_LEN+1);
            memset(buf, 0, FAT32_BPB_BOOTCODE_LEN+1);
            isFat32 = true;
        }
        else
        {
            /* Assume it is FAT16 */
            buf = (char*)malloc(FAT16_BPB_BOOTCODE_LEN+1);
            memset(buf, 0, FAT16_BPB_BOOTCODE_LEN+1);
            isFat32 = false;
        }

        /* Generate serial key & format it to a buffer */
        UsbKey usbKey;
        SerialStamp serialStamp;

        serialStamp.usbninjaSignature = usbKey.usbninjaSignature;
        serialStamp.serial = usbKey.generateRandStr(25);
        serialStamp.crc32 = usbKey.generateCrc32((unsigned char*)serialStamp.serial.c_str(),
                                                 serialStamp.serial.length());

        sprintf(buf, "%s%s%s", serialStamp.usbninjaSignature, serialStamp.serial.c_str(),
                serialStamp.crc32.c_str());

        UsbBPB bpb;
        bpb.openDevice(drvLtr);
        if (isFat32)
        {
            if (!bpb.writeBPBCode32((unsigned char*)buf))
            {
                QMessageBox::critical(this, "Error", "There was an error writing the raw data to the "
                                      "usb disk, please make sure you have sufficient privileges then "
                                      "try again.");
                return;
            }
        }
        else
        {
            if (!bpb.writeBPBCode16((unsigned char*)buf))
            {
                QMessageBox::critical(this, "Error", "There was an error writing the raw data to the "
                                      "usb disk, please make sure you have sufficient privileges then "
                                      "try again.");
                return;
            }
        }

        /* Log authorized drive to the database */
        AuthDrive drv;

        drv.date = drv.dateAndTime();
        drv.serial = serialStamp.serial;

        if (strcmp(ui->plainTextEdit->toPlainText().toStdString().c_str(), "Add description here.") == 0)
            drv.notes = " ";
        else
            drv.notes = ui->plainTextEdit->toPlainText().toStdString();

        drv.driveName = drvInfoS.driveName;
        drv.driveSize = drvInfoS.diskSize;
        drv.logEntry();
    }
    else
        QMessageBox::critical(this, "Error", "Error, please select a valid drive letter.");
}
