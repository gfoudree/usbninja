#include "accesslog.h"

AccessLog::AccessLog()
{
}

bool AccessLog::logUsbDrive(logUSB &lUsb)
{
    Sql sql("C:\\users\\grant\\desktop\\log.db");
    std::stringstream sqlStatement;
    sqlStatement << "INSERT INTO loggedDrives (accepted, date, user, driveLetter, driveName, driveLabel, ";
    sqlStatement << "driveSize, driveSerial, driveGUID, usbninjaSerial) VALUES (" << lUsb.accepted << ", \'";
    sqlStatement << lUsb.date << "\', \'" << lUsb.user << "\', \'" << lUsb.driveLetter << "\', \'" << lUsb.driveName;
    sqlStatement << "\', \'" << lUsb.driveLabel << "\', " << lUsb.driveSize << ", \'" << lUsb.driveSerial;
    sqlStatement << "\', \'" << lUsb.driveGUID << "\', \'" << lUsb.usbninjaSerial << "\');";
    sql.dbExecSql((char*)sqlStatement.str().c_str());

    ErrorLog::logErrorToFile((char*)sqlStatement.str().c_str());
    return true;
}

void AccessLog::createLogStruct(logUSB *lUsb, char drvLtr)
{
    lUsb->date = ErrorLog::dateAndTime();
    lUsb->user = AccessLog::userName();
    lUsb->driveLetter = drvLtr;

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
