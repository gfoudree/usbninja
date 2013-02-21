#ifndef ERRORLOG_H
#define ERRORLOG_H

#define _WIN32_WINNT 0x601
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <windows.h>
#include <memory>

class ErrorLog
{
public:
    static void logErrorToFile(char *errLevel = "*NORMAL*", char *errMsg = "", char *extra = "", char *extra_2 = "", char *extra_3 = "");
    static std::string dateAndTime();
    static char *winErrToStr(DWORD errCode);

    ErrorLog();
};

#endif // ERRORLOG_H
