/*
 * Copyright (C) by Grant Foudree <grant907@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */
 #ifndef ERRORLOG_H
#define ERRORLOG_H

#define _WIN32_WINNT 0x601
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <windows.h>
#include <memory>
#include <direct.h>

#include "paths.h"
class ErrorLog
{
public:
    __declspec(dllexport) static void logErrorToFile(char *errLevel = "*NORMAL*", char *errMsg = "", char *extra = "", char *extra_2 = "", char *extra_3 = "");
    __declspec(dllexport) static std::string dateAndTime();
    __declspec(dllexport) static char *winErrToStr(DWORD errCode);

    __declspec(dllexport) ErrorLog();
};

#endif // ERRORLOG_H
