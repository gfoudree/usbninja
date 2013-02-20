#ifndef SQL_H
#define SQL_H

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "errorlog.h"

struct sqlDriveStruct;

class Sql
{
protected:
    sqlite3 *db;
    static int sqlCallback(void *dataPtr, int argc, char **argv, char **colname);

public:
    bool dbConnect(char *filename);
    void dbDisconnect();
    bool dbExecSql(char *sqlStmt);
    void queryDrives(std::vector<sqlDriveStruct> *drives);

    Sql();
    Sql(char *filename);
    ~Sql();
};

struct sqlDriveStruct
{
    int id;
    std::string date;
    std::string serial;
    std::string driveName;
    unsigned int driveSize;
};

#endif // SQL_H
