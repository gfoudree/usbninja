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

void threadHandler(char driveLtr)
{
    /*
    Sql sql;
    sql.dbConnect("C:\\users\\grant\\desktop\\database.db");
    std::vector<sqlDriveStruct> drvs;
    sql.queryDrives(&drvs);

    std::cout << drvs.at(0).date;

    UsbOps ops;
    ops.lockUSB(driveLtr);
    ops.ejectUSB();
    */

    boost::shared_ptr<AccessLog> log(new AccessLog);
    log->createLogStruct(&log->logUSBStruct, driveLtr);
    log->logUsbDrive(log->logUSBStruct);
}
