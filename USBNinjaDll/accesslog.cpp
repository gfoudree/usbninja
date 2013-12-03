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
 #include "accesslog.h"

AccessLog::AccessLog()
{
}

bool AccessLog::logUsbDrive(logUSB &lUsb, bool mysql)
{
    Sql sql((char*)Paths::getDatabasePath().c_str());

    std::stringstream sqlStatement;
    sqlStatement << "INSERT INTO loggedDrives (accepted, date, user, driveLetter, driveName, driveLabel, ";
    sqlStatement << "driveSize, driveSerial, driveGUID, usbninjaSerial) VALUES (\'" << lUsb.accepted << "\', \'";
    sqlStatement << lUsb.date << "\', \'" << lUsb.user << "\', \'" << lUsb.driveLetter << "\', \'" << lUsb.driveName;
    sqlStatement << "\', \'" << lUsb.driveLabel << "\', \'" << lUsb.driveSize << "\', \'" << lUsb.driveSerial;
    sqlStatement << "\', \'";
    if (!lUsb.driveGUID.empty())
        sqlStatement << lUsb.driveGUID << "\\";
    else
        sqlStatement << lUsb.driveGUID;
    sqlStatement << "\', \'" << lUsb.usbninjaSerial << "\')";

    std::string tmp = sqlStatement.str();
    char *stmt = (char*)tmp.c_str();

    if (mysql)
    {
        MySQLDB db;
        ConfigParser configParser((char*)Paths::getConfigPath().c_str());
        sqlSettings settings = configParser.getSqlSettings();

        db.dbConnect(settings.ip.c_str(), settings.username.c_str(),
                     settings.password.c_str(), settings.database.c_str(),
                     settings.port);
        db.dbExecSql(stmt);
    }
    return sql.dbExecSql(stmt);
}

void AccessLog::createLogStruct(logUSB *lUsb, char drvLtr, char *usbNinjaSerial)
{
    lUsb->date = ErrorLog::dateAndTime();
    lUsb->user = AccessLog::userName();
    lUsb->driveLetter = drvLtr;
    lUsb->usbninjaSerial = usbNinjaSerial;

    std::string devId;
    UsbDevice::GetDriveDeviceId(drvLtr, &devId);
    UsbDevice::GetFriendlyName(devId, &lUsb->driveName);
    UsbDevice::GetVolumeSize(drvLtr, &lUsb->driveSize);
    UsbDevice::GetVolumeSerial(drvLtr, &lUsb->driveSerial);
    UsbDevice::GetVolumeGUID(drvLtr, &lUsb->driveGUID);
    UsbDevice::GetVolumeLabel(drvLtr, &lUsb->driveLabel);
}

std::string AccessLog::userName()
{
    char username[UNLEN+1];
    DWORD unLen = UNLEN;
    if (!GetUserNameA(username, &unLen))
        ErrorLog::logErrorToFile("Unable to get username: ", ErrorLog::winErrToStr(GetLastError()));
    return username;
}
