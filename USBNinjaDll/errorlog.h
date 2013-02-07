#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

class ErrorLog
{
public:
    static void logErrorToFile(char *errMsg);
    static std::string dateAndTime();

    ErrorLog();
};

#endif // ERRORLOG_H
