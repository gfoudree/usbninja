#include "accesslog.h"

AccessLog::AccessLog()
{
}

bool AccessLog::logUsbDrive(logUSB &lUsb)
{
    Sql sql("C:\\users\\grant\\desktop\\log.db");
    std::stringstream sqlStatement;
    sqlStatement << "INSERT INTO loggedDrives (accepted, date, user, driveLetter, driveName, ";
    sqlStatement << "driveSize, driveSerial, driveGUID, volumeID) VALUES (" << lUsb.accepted << ", \'" << lUsb.date;
    sqlStatement << "\', \'" << lUsb.user << "\', \'" << lUsb.driveLetter << "\', \'" << lUsb.driveName;
    sqlStatement << "\', " << lUsb.driveSize << ", \'" << lUsb.driveSerial;
    sqlStatement << "\', \'" << lUsb.driveGUID << "\', \'" << lUsb.volumeID << "\');";
    sql.dbExecSql((char*)sqlStatement.str().c_str());

    ErrorLog::logErrorToFile((char*)sqlStatement.str().c_str());
    return true;
}
