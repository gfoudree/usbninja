#include "sql.h"

Sql::Sql()
{
}

Sql::~Sql()
{
    dbDisconnect();
}

bool Sql::dbConnect(char *filename)
{
    int res;
    res = sqlite3_open_v2(filename, &db, SQLITE_OPEN_READWRITE, 0);
    if (res != SQLITE_OK)
    {
        if (res == SQLITE_CANTOPEN)
        {
            res = sqlite3_open(filename, &db);
            if (res == SQLITE_OK)
            {
                dbExecSql("CREATE TABLE authorizedDrives (id int AUTO_INCREMENT, serial char(100));");
                dbExecSql("CREATE TABLE loggedDrives (id int AUTO_INCREMENT, driveltr char(5), serial char(100));");
                ErrorLog::logErrorToFile("Created new SQL database.");
                return true;
            }
            else
            {
                ErrorLog::logErrorToFile("*CRITICAL*", "Error accessing local SQL database: ", (char*)sqlite3_errstr(res));
                return false;
            }
        }
    }
    else
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
