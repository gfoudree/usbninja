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
 #include "sql.h"

Sql::Sql()
{
}

Sql::Sql(char *filename)
{
    dbConnect(filename, false);
}

Sql::~Sql()
{
    dbDisconnect();
}

bool Sql::dbConnect(char *filename, bool createNew)
{
    int res;
    res = sqlite3_open_v2(filename, &db, SQLITE_OPEN_READWRITE, 0);
    if (res != SQLITE_OK)
    {
        if ((res == SQLITE_CANTOPEN) && createNew == true)
        {
            res = sqlite3_open(filename, &db);
            if (res == SQLITE_OK)
            {
                dbExecSql("CREATE TABLE authDrives (id INTEGER PRIMARY KEY, dateAuthorized CHAR(20), serial CHAR(120), driveName CHAR(30), driveSize INTEGER, " \
                          "notes CHAR(256));");
                dbExecSql("CREATE TABLE loggedDrives (id INTEGER PRIMARY KEY, accepted INT, date CHAR(50), user CHAR(50), driveLetter CHAR(1), driveName CHAR(50), " \
                          "driveLabel CHAR(50), driveSize BIGINT, driveSerial CHAR(100), driveGUID CHAR(50), usbninjaSerial CHAR(100));");
                ErrorLog::logErrorToFile("*INFO*", "Created new SQL database.");
                return true;
            }
            else
            {
                ErrorLog::logErrorToFile("*CRITICAL*", "Error accessing local SQL database: ", (char*)sqlite3_errstr(res));
                return false;
            }
        }
        else
            return false;
    }
    return true;
}

bool Sql::dbExecSql(char *sqlStmt)
{
    char *errMsg = NULL;
    if (sqlite3_exec(db, sqlStmt, NULL, NULL, &errMsg) != SQLITE_OK)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Error executing SQL statement:", errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    sqlite3_free(errMsg);
    return true;
}

void Sql::dbDisconnect()
{
    sqlite3_close(db);
}

int Sql::sqlLogCallback(void *dataPtr, int argc, char **argv, char **colname)
{
    logUSB tmpUsb;
    tmpUsb.accepted = atoi(argv[1]);
    tmpUsb.date = argv[2];
    tmpUsb.user = argv[3];
    tmpUsb.driveLetter = argv[4][0];
    tmpUsb.driveName = argv[5];
    tmpUsb.driveLabel = argv[6];
    tmpUsb.driveSize = atoi(argv[7]);
    tmpUsb.driveSerial = argv[8];
    tmpUsb.driveGUID = argv[9];
    tmpUsb.usbninjaSerial = argv[10];

    std::vector<logUSB> *pLogStruct = static_cast<std::vector<logUSB>*>(dataPtr);
    pLogStruct->push_back(tmpUsb);
    return 0;
}


int Sql::sqlAuthedDrivesCallback(void *dataPtr, int argc, char **argv, char **colname)
{
    authedDrive tmpDrv;
    tmpDrv.id = atoi(argv[0]);
    tmpDrv.dateAuthorized = argv[1];
    tmpDrv.serial = argv[2];
    tmpDrv.driveName = argv[3];
    tmpDrv.driveSize = atoi(argv[4]);
    tmpDrv.notes = argv[5];

    std::vector<authedDrive> *pParamStruct = static_cast<std::vector<authedDrive>*>(dataPtr);
    pParamStruct->push_back(tmpDrv);
    return 0;
}

int Sql::sqlCountCallback(void *dataPtr, int argc, char **argv, char **colname)
{
    DriveCount *dc = (DriveCount*)dataPtr;

    for (int i = 0; i < argc; i++)
    {
        if (atoi(argv[i]) == true)
            dc->acceptedDrives += 1;
        else if (atoi(argv[i]) == false)
            dc->deniedDrives += 1;
    }
    return 0;
}

void Sql::queryLog(std::vector<logUSB> *drives)
{
    char *errBuf;
    if (sqlite3_exec(db, "SELECT * FROM loggedDrives;", sqlLogCallback, static_cast<void*>(drives), &errBuf) != 0)
        ErrorLog::logErrorToFile("*CRITICAL*", "Error reading logfile: ", errBuf);
}

void Sql::queryAuthedDrives(std::vector<authedDrive> *drives)
{
    char *errBuf;
    if (sqlite3_exec(db, "SELECT * FROM authDrives;", sqlAuthedDrivesCallback, static_cast<void*>(drives), &errBuf) != 0)
        ErrorLog::logErrorToFile("*CRITICAL*", "Error reading logfile: ", errBuf);

    std::sort(drives->begin(), drives->end(), [](const authedDrive &class1, const authedDrive &class2) -> bool
    {
        return (class1.id > class2.id);
    }); //Sort vector by ID
}

int Sql::authorizedDrives()
{
    DriveCount driveCount = {0};
    char *errBuf;
    if (sqlite3_exec(db, "SELECT accepted FROM loggedDrives;", sqlCountCallback, (void*)&driveCount, &errBuf) != 0)
        ErrorLog::logErrorToFile("*CRITICAL*", "Error counting authorized drives: ", errBuf);
    return driveCount.acceptedDrives;
}

int Sql::deniedDrives()
{
    DriveCount driveCount = {0};
    char *errBuf;
    if (sqlite3_exec(db, "SELECT accepted FROM loggedDrives;", sqlCountCallback, (void*)&driveCount, &errBuf) != 0)
        ErrorLog::logErrorToFile("*CRITICAL*", "Error counting authorized drives: ", errBuf);
    return driveCount.deniedDrives;
}
