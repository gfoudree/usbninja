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
                std::string errStr = "Error accessing local SQL database: ";
                errStr.append(sqlite3_errstr(res));
                ErrorLog::logErrorToFile((char*)errStr.c_str());
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
        std::string errStr = "Error executing SQL statement: ";
        errStr.append(errMsg);
        ErrorLog::logErrorToFile((char*)errStr.c_str());
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
