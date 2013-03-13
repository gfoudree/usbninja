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
