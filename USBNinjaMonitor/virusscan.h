#ifndef VIRUSSCAN_H
#define VIRUSSCAN_H

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>
class VirusScan
{
protected:
    std::string getFileExtention(std::string fileName);

    const static unsigned int fTypesSz = 14;
    char* fTypes[fTypesSz];

public:
    void lockFiles(std::vector<std::string> files);
    std::vector<std::string> findFiles(char devName);
    VirusScan();
};

#endif // VIRUSSCAN_H
