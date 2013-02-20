#ifndef ACCESSLOG_H
#define ACCESSLOG_H

#include <iostream>
#include <stdio.h>
#include <sstream>
#include "sql.h"

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
        unsigned int    driveSize;
        std::string     driveSerial;
        std::string     driveGUID;
        std::string     volumeID;
    } logUSBStruct;

    static bool logUsbDrive(logUSB &lUsb);
    AccessLog();
};



#endif // ACCESSLOG_H
