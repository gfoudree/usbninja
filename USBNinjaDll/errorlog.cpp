#include "errorlog.h"

ErrorLog::ErrorLog()
{
}

void ErrorLog::logErrorToFile(char *errLevel, char *errMsg, char *extra, char *extra_2, char *extra_3)
{
    std::ofstream logfile;
    logfile.open("C:\\users\\grant\\desktop\\log.txt", std::ios::app);
    if (logfile.is_open())
    {
        logfile << "[" << dateAndTime() << "] ";
        logfile << errLevel << " " << errMsg << extra << extra_2 << extra_3 << std::endl;
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
