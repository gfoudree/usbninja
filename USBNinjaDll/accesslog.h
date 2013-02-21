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

    static bool logUsbDrive(logUSB &lUsb);
    static std::string userName();
    void createLogStruct(logUSB *lUsb, char drvLtr);
    AccessLog();
};



#endif // ACCESSLOG_H
