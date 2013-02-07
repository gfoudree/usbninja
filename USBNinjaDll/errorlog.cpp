#include "errorlog.h"

ErrorLog::ErrorLog()
{
}

void ErrorLog::logErrorToFile(char *errMsg)
{
    std::ofstream logfile;
    logfile.open("C:\\users\\grant\\desktop\\log.txt", std::ios::app);
    if (logfile.is_open())
    {
        logfile << "[" << dateAndTime() << "] " << errMsg << std::endl;
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
