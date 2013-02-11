#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

class ErrorLog
{
public:
    static void logErrorToFile(char *errLevel = "*NORMAL*", char *errMsg = "", char *extra = "", char *extra_2 = "", char *extra_3 = "");
    static std::string dateAndTime();

    ErrorLog();
};

#endif // ERRORLOG_H
