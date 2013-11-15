#ifndef MYSQLDB_H
#define MYSQLDB_H

#include <mysql.h>

class MySQLDB
{
    MYSQL *conn;

public:
    static const char *authDrivesSQL;
    static const char *loggedDrivesSQL;

    bool dbConnect(const char *ip, const char *username, const char *password,
                   const char *database, unsigned int port);
    bool dbCreateTables();

    MySQLDB();
    ~MySQLDB();
};

#endif // MYSQLDB_H
