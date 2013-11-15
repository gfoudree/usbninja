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
        //log error
        return false;
    }
    return true;
}

bool MySQLDB::dbCreateTables()
{
    if (mysql_query(conn, MySQLDB::authDrivesSQL) != 0)
    {
        //log error
        return false;
    }
    if (mysql_query(conn, MySQLDB::loggedDrivesSQL) != 0)
    {
        //log error
        return false;
    }
    return true;
}
