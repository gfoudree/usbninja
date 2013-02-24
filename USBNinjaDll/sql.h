#ifndef SQL_H
#define SQL_H

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "errorlog.h"

struct sqlDriveStruct;
struct logUSB;

class Sql
{
protected:
    sqlite3 *db;
    static int sqlAuthCallback(void *dataPtr, int argc, char **argv, char **colname);
    static int sqlLogCallback(void *dataPtr, int argc, char **argv, char **colname);

public:
    __declspec(dllexport) bool dbConnect(char *filename);
    __declspec(dllexport) void dbDisconnect();
    __declspec(dllexport) bool dbExecSql(char *sqlStmt);
    __declspec(dllexport) void queryDrives(std::vector<sqlDriveStruct> *drives);
    __declspec(dllexport) void queryLog(std::vector<logUSB> *drives);

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

#endif // SQL_H
