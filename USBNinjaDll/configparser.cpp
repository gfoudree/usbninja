#include "configparser.h"

void ConfigParser::parseLine(std::string line)
{
    char *ptr = strtok((char*)line.c_str(), "=");
    var.push_back(ptr);
    ptr = strtok(NULL, "=");
    value.push_back(ptr);
}

std::string ConfigParser::getValue(std::string varStr)
{
    int pos;
    std::vector<std::string>::iterator it;
    it = std::find(var.begin(), var.end(), varStr);
    if (it != var.end())
    {
        pos = std::distance(var.begin(), it);
        return value.at(pos);
    }
    else
        return "";
}

std::string ConfigParser::getData()
{
    return configFileData;
}

bool ConfigParser::setValue(std::string varStr, std::string valueStr)
{
    std::ofstream hFile(configFile.c_str(), std::ios::app);
    if (hFile.is_open())
    {
        hFile << varStr.c_str() << "=" << valueStr.c_str() << "\n";
        hFile.close();
        return true;
    }
    else
        return false;
}
