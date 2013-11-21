#ifndef MYSQLDB_H
#define MYSQLDB_H

#include <mysql.h>

#include "errorlog.h"
#include "sql.h"

class MySQLDB
{
    MYSQL *conn;

public:
     __declspec(dllexport) static const char *authDrivesSQL;
     __declspec(dllexport) static const char *loggedDrivesSQL;

     __declspec(dllexport) bool dbConnect(const char *ip, const char *username, const char *password,
                   const char *database, unsigned int port);
     __declspec(dllexport) bool dbCreateTables();
     __declspec(dllexport) void queryLog(std::vector<logUSB> *drives);
     __declspec(dllexport) void queryAuthedDrives(std::vector<authedDrive> *drives);
     __declspec(dllexport) int authorizedDrives();
     __declspec(dllexport) int deniedDrives();

     __declspec(dllexport) MySQLDB();
     __declspec(dllexport) ~MySQLDB();
};

#endif // MYSQLDB_H
