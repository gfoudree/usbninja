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
 #ifndef ACCESSLOG_H
#define ACCESSLOG_H

#define _WIN32_WINNT 0x601
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#include <lmcons.h>
#include "sql.h"
#include "usbdevice.h"
#include "paths.h"

struct logUSB;

class AccessLog : public Sql
{
public:

    struct logUSB
    {
        bool            accepted;
        std::string     date;
        std::string     user;
        char            driveLetter;
        std::string     driveName;
        std::string     driveLabel;
        unsigned int    driveSize;
        std::string     driveSerial;
        std::string     driveGUID;
        std::string     usbninjaSerial;
    } logUSBStruct;

    __declspec(dllexport) static bool logUsbDrive(logUSB &lUsb);
    __declspec(dllexport) static std::string userName();
    __declspec(dllexport) void createLogStruct(logUSB *lUsb, char drvLtr, char *usbNinjaSerial);
    __declspec(dllexport) AccessLog();
};



#endif // ACCESSLOG_H
