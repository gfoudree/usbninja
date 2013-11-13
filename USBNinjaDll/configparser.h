#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>

class ConfigParser
{
    std::string configFile;
    std::string configFileData;
    std::vector<std::string> var, value;

    void parseLine(std::string line);

public:
    ConfigParser(char *cfgFile) : configFile(cfgFile)
    {
        std::string dataTemp;
        std::ifstream hFile(configFile.c_str());
        while (hFile.good())
        {
            std::getline(hFile, dataTemp);
            if ((dataTemp.at(0) != '#') && ((dataTemp.find('=')) != std::string::npos))
            {
                configFileData.append(dataTemp);
                parseLine(dataTemp);
            }
        }
    }

    std::string getValue(std::string varStr);
    std::string getData();
};

#endif // CONFIGPARSER_H
