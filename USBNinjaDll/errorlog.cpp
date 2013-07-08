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
 #include "errorlog.h"

ErrorLog::ErrorLog()
{
}

void ErrorLog::logErrorToFile(char *errLevel, char *errMsg, char *extra, char *extra_2, char *extra_3)
{
    std::ofstream logfile;
    logfile.open(Paths::getLogPath().c_str(), std::ios::app);
    if (logfile.is_open())
    {
        logfile << "[" << dateAndTime() << "] ";
        logfile << errLevel << " " << errMsg << extra << extra_2 << extra_3 << std::endl;
        logfile.flush();
    }
    logfile.close();
}

std::string ErrorLog::dateAndTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);
    return buf;
}

char *ErrorLog::winErrToStr(DWORD errCode)
{
    char *buf;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf, 0, NULL);
    return buf;
}
