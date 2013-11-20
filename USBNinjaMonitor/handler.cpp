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

    bool authorized = false;

    /* Lock the USB drive */
    UsbOps ops;
    ops.lockUSB(driveLtr);

    /* Query authorized devices */
    Sql sql;
    if (!sql.dbConnect((char*)Paths::getDatabasePath().c_str(), false))
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to open authorized drives database!");
        gMutex.unlock();
        return;
    }
    std::vector<sqlDriveStruct> drvs;
    sql.queryDrives(&drvs);

    /* Get the serial key of the device */
    UsbKey usbKey;
    UsbKeyhdr hdr;

    ops.unlockUSB();
    usbKey.getUsbKeyHdr(&hdr, driveLtr);
    ops.lockUSB(driveLtr);

    /* Check if the serial exists in the database */
    for (std::vector<sqlDriveStruct>::iterator it = drvs.begin(); it != drvs.end(); it++)
    {
        std::cout << it->serial.c_str() << " " << hdr.serialkey.c_str() << std::endl;
        if (it->serial.compare(hdr.serialkey) == 0)
        {
            authorized = true;
            break;
        }
    }

    ops.unlockUSB();

    /* Log media insertion event */

    boost::shared_ptr<AccessLog> log(new AccessLog);
    log->createLogStruct(&log->logUSBStruct, driveLtr, (char*)hdr.serialkey.c_str());
    log->logUSBStruct.accepted = authorized;
    log->logUsbDrive(log->logUSBStruct);

    if (!authorized)
    {
        ops.lockUSB(driveLtr);
        ops.ejectUSB();
    }
    gMutex.unlock();
}
