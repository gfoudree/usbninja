#ifndef SQL_H
#define SQL_H

#include <sqlite3.h>
#include <iostream>
#include "errorlog.h"

class Sql
{
protected:
    sqlite3 *db;

public:
    bool dbConnect(char *filename);
    void dbDisconnect();
    bool dbExecSql(char *sqlStmt);
    Sql();
    ~Sql();
};

#endif // SQL_H
