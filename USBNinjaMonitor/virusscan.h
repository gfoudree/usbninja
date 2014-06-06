#ifndef VIRUSSCAN_H
#define VIRUSSCAN_H

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <clamav/clamav.h>

#include "traynotify.h"
#include "../../USBNinjaDll/errorlog.h"

class VirusScan
{
protected:
    std::string getFileExtention(std::string fileName);

    char *virusName;
    struct cl_engine *cl;
    unsigned int numSignatures;

    const static unsigned int fTypesSz = 14;
    char* fTypes[fTypesSz];

public:
    static cl_cvd getCVDInfo(char *file);
    void lockFiles(std::vector<std::string> files);
    std::vector<std::string> findFiles(char devName);
    char *getVirusName();

    VirusScan(TrayNotify *tn);
    ~VirusScan();
};

#endif // VIRUSSCAN_H
