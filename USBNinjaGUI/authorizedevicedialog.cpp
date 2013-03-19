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
}

AuthorizeDeviceDialog::~AuthorizeDeviceDialog()
{
    delete ui;
}
