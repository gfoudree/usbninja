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
    __declspec(dllexport) static void logErrorToFile(char *errLevel = "*NORMAL*", char *errMsg = "", char *extra = "", char *extra_2 = "", char *extra_3 = "");
    __declspec(dllexport) static std::string dateAndTime();
    __declspec(dllexport) static char *winErrToStr(DWORD errCode);

    __declspec(dllexport) ErrorLog();
};

#endif // ERRORLOG_H
