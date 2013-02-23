#include "sql.h"

Sql::Sql()
{
}

Sql::Sql(char *filename)
{
    dbConnect(filename);
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
                dbExecSql("CREATE TABLE authDrives (id INTEGER PRIMARY KEY, dateAuthorized CHAR(20), serial CHAR(120), driveName CHAR(30), driveSize INTEGER);");
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


int Sql::sqlCallback(void *dataPtr, int argc, char **argv, char **colname)
{
    sqlDriveStruct tmpDrv;
    tmpDrv.id = atoi(argv[0]);
    tmpDrv.date = argv[1];
    tmpDrv.serial = argv[2];
    tmpDrv.driveName = argv[3];
    tmpDrv.driveSize = atoi(argv[4]);

    std::vector<sqlDriveStruct> *pParamStruct = static_cast<std::vector<sqlDriveStruct>*>(dataPtr);
    pParamStruct->push_back(tmpDrv);
    return 0;
}

void Sql::queryDrives(std::vector<sqlDriveStruct> *drives)
{
    char *errBuf;
    if (sqlite3_exec(db, "SELECT * FROM authDrives;", sqlCallback, static_cast<void*>(drives), &errBuf) != 0)
        ErrorLog::logErrorToFile("*CRITICAL*", "Error reading authorized USB drives: ", errBuf);
}
