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
 
#include "handler.h"

extern boost::mutex gMutex;

void threadHandler(char driveLtr)
{
    /* Lock the mutex so we don't try and access the database at the same time */
    gMutex.lock();

    /* Lock the USB drive */
    UsbOps ops;
    //ops.lockUSB(driveLtr); //Causes a problem with raw read/write beacuse of the locking drive, fix it

    /* Query authorized devices */
    Sql sql;

    if (!sql.dbConnect("C:\\users\\grant\\desktop\\log.db", false))
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to open authorized drives database!");
        //Eject the drive!
        gMutex.unlock();
        return;
    }
    std::vector<sqlDriveStruct> drvs;
    sql.queryDrives(&drvs);

    /* Get the serial key of the device */
    UsbKey usbKey;
    UsbKeyhdr hdr;

    usbKey.getUsbKeyHdr(&hdr, driveLtr);

    for (std::vector<sqlDriveStruct>::iterator it = drvs.begin(); it != drvs.end(); it++)
    {
        std::cout << it->serial.c_str() << " " << hdr.serialkey.c_str() << std::endl;
        if (it->serial.compare(hdr.serialkey) == 0)
        {
            //It's authorized, do something
        }
    }

    /* Log media insertion event */
    /*
    boost::shared_ptr<AccessLog> log(new AccessLog);
    log->createLogStruct(&log->logUSBStruct, driveLtr);
    log->logUsbDrive(log->logUSBStruct);
    */

end:
    //ops.unlockUSB();
    gMutex.unlock();
}
