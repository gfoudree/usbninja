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

    AccessLog *log = new AccessLog;
    log->logUSBStruct.accepted = true;
    log->logUSBStruct.date = "2/19/13_7:47PM";
    log->logUSBStruct.driveGUID = "ffwe990aa0jf";
    log->logUSBStruct.driveLetter = 'E';
    log->logUSBStruct.driveName = "PENDRIVE";
    log->logUSBStruct.driveSerial = "0xff31f9019";
    log->logUSBStruct.driveSize = 40960;
    log->logUSBStruct.user = "Gmoney";
    log->logUSBStruct.volumeID = "004001414";
    log->logUsbDrive(log->logUSBStruct);
    delete log;
}
