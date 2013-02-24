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

    __declspec(dllexport) static bool logUsbDrive(logUSB &lUsb);
    __declspec(dllexport) static std::string userName();
    __declspec(dllexport) void createLogStruct(logUSB *lUsb, char drvLtr);
    __declspec(dllexport) AccessLog();
};



#endif // ACCESSLOG_H
