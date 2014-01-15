#include "mysqldb.h"

const char *MySQLDB::authDrivesSQL = "CREATE TABLE authDrives " \
        "(id INTEGER PRIMARY KEY, dateAuthorized " \
        "CHAR(20), serial CHAR(120), driveName CHAR(30), driveSize INTEGER, " \
        "notes CHAR(255));";
const char *MySQLDB::loggedDrivesSQL = "CREATE TABLE loggedDrives " \
        "(id INTEGER PRIMARY KEY, accepted INT, date CHAR(50), user CHAR(50),"
        "driveLetter CHAR(1), driveName CHAR(50), driveLabel CHAR(50), driveSize " \
        "BIGINT, driveSerial CHAR(100), driveGUID CHAR(50), usbninjaSerial CHAR(100));";

MySQLDB::MySQLDB()
{
    conn = mysql_init(NULL);
}

MySQLDB::~MySQLDB()
{
    mysql_close(conn);
}

bool MySQLDB::dbConnect(const char *ip, const char *username, const char *password, const char *database, unsigned int port)
{
    if (!mysql_real_connect(conn, ip, username, password, database, port, NULL, 0))
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to connect to database ", (char*)mysql_error(conn));
        return false;
    }
    return true;
}

bool MySQLDB::dbCreateTables()
{
    if (mysql_query(conn, MySQLDB::authDrivesSQL) != 0)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to create table ", (char*)mysql_error(conn));
        return false;
    }
    if (mysql_query(conn, MySQLDB::loggedDrivesSQL) != 0)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to create table ", (char*)mysql_error(conn));
        return false;
    }
    return true;
}

void MySQLDB::queryAuthedDrives(std::vector<authedDrive> *drives)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    authedDrive tmpDrv;

    if (mysql_query(conn, "SELECT * FROM authDrives") != 0)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to run MySQL query ", (char*)mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);

    while ((row = mysql_fetch_row(res)))
    {
        tmpDrv.id = atoi(row[0]);
        tmpDrv.dateAuthorized = row[1];
        tmpDrv.serial = row[2];
        tmpDrv.driveName = row[3];
        tmpDrv.driveSize = atoi(row[4]);
        tmpDrv.notes = row[5];

        drives->push_back(tmpDrv);
    }
    mysql_free_result(res);

    std::sort(drives->begin(), drives->end(), [] (const authedDrive &class1, const authedDrive &class2)
        -> bool
    {
        return (class1.id > class2.id);
    });
}

void MySQLDB::queryLog(std::vector<logUSB> *drives)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    logUSB tmpDrv;

    if (mysql_query(conn, "SELECT * FROM loggedDrives") != 0)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to run MySQL query ", (char*)mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);

    while ((row = mysql_fetch_row(res)))
    {
        tmpDrv.accepted = atoi(row[1]);
        tmpDrv.date = row[2];
        tmpDrv.user = row[3];
        tmpDrv.driveLetter = row[4][0];
        tmpDrv.driveName = row[5];
        tmpDrv.driveLabel = row[6];
        tmpDrv.driveSize = atoi(row[7]);
        tmpDrv.driveSerial = row[8];
        tmpDrv.driveGUID = row[9];
        tmpDrv.usbninjaSerial = row[10];

        drives->push_back(tmpDrv);
    }
    mysql_free_result(res);
}

int MySQLDB::authorizedDrives()
{
    MYSQL_RES *res;

    if (mysql_query(conn, "SELECT accepted FROM loggedDrives WHERE accepted=1") != 0)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to run MySQL query ", (char*)mysql_error(conn));
        return 0;
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}

int MySQLDB::deniedDrives()
{
    MYSQL_RES *res;

    if (mysql_query(conn, "SELECT accepted FROM loggedDrives WHERE accepted=0") != 0)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to run MySQL query ", (char*)mysql_error(conn));
        return 0;
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}

bool MySQLDB::dbExecSql(char *str)
{
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);

    if ((mysql_stmt_prepare(stmt, str, strlen(str)) != 0) ||
            mysql_stmt_execute(stmt) != 0)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to run MySQL query ", (char*)mysql_error(conn));
        mysql_stmt_close(stmt);
        return false;
    }
    else
    {
        mysql_stmt_close(stmt);
        return true;
    }
}
