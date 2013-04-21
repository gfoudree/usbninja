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
 #ifndef SQL_H
#define SQL_H

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "errorlog.h"

struct sqlDriveStruct;
struct logUSB;
struct authedDrive;

class Sql
{
protected:
    sqlite3 *db;
    static int sqlAuthCallback(void *dataPtr, int argc, char **argv, char **colname);
    static int sqlLogCallback(void *dataPtr, int argc, char **argv, char **colname);
    static int sqlAuthedDrivesCallback(void *dataPtr, int argc, char **argv, char **colname);
    static int sqlCountCallback(void *dataPtr, int argc, char **argv, char **colname);


public:
    __declspec(dllexport) bool dbConnect(char *filename);
    __declspec(dllexport) void dbDisconnect();
    __declspec(dllexport) bool dbExecSql(char *sqlStmt);
    __declspec(dllexport) void queryDrives(std::vector<sqlDriveStruct> *drives);
    __declspec(dllexport) void queryLog(std::vector<logUSB> *drives);
    __declspec(dllexport) void queryAuthedDrives(std::vector<authedDrive> *drives);
    __declspec(dllexport) int authorizedDrives();
    __declspec(dllexport) int deniedDrives();

    __declspec(dllexport) Sql();
    __declspec(dllexport) Sql(char *filename);
    __declspec(dllexport) ~Sql();
};

struct sqlDriveStruct
{
    int id;
    std::string date;
    std::string serial;
    std::string driveName;
    unsigned int driveSize;
};

struct logUSB
{
    bool            accepted;
    std::string     date;
    std::string     user;
    char            driveLetter;
    std::string     driveName;
    std::string     driveLabel;
    unsigned int    driveSize;
    std::string     driveSerial;
    std::string     driveGUID;
    std::string     usbninjaSerial;
};

struct authedDrive
{
    std::string     dateAuthorized;
    std::string     serial;
    std::string     driveName;
    unsigned int    driveSize;
    std::string     notes;
};

struct DriveCount
{
    int acceptedDrives, deniedDrives;
    bool countType;
    //true = count authorized drives, false = count blocked drives
};

#endif // SQL_H
