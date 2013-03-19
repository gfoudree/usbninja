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

#ifndef AUTHORIZEDEVICEDIALOG_H
#define AUTHORIZEDEVICEDIALOG_H

#include <QDialog>
#include <vector>
#include <iostream>

#include "../../USBNinjaDll/usbdevice.h"
namespace Ui {
class AuthorizeDeviceDialog;
}

class AuthorizeDeviceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AuthorizeDeviceDialog(QWidget *parent = 0);
    ~AuthorizeDeviceDialog();
    
private:
    Ui::AuthorizeDeviceDialog *ui;
};

#endif // AUTHORIZEDEVICEDIALOG_H
