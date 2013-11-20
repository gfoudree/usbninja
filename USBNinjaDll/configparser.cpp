#include "configparser.h"

void ConfigParser::parseLine(std::string line)
{
    char *ptr = strtok((char*)line.c_str(), "=");
    var.push_back(ptr);
    ptr = strtok(NULL, "=");
    if (ptr != NULL)
        value.push_back(ptr);
    else
        value.push_back("");
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
    int pos;
    std::vector<std::string>::iterator it;
    it = std::find(var.begin(), var.end(), varStr);
    if (it != var.end())
    {
        pos = std::distance(var.begin(), it);
        value[pos] = valueStr;
    }
    else
    {
        value.push_back(valueStr);
        var.push_back(varStr);
    }

    std::fstream hFile(configFile.c_str(), std::fstream::out | std::fstream::trunc);
    if (hFile.is_open())
    {
        std::vector<std::string>::iterator varIt, valueIt;
        for (varIt = var.begin(), valueIt = value.begin(); varIt != var.end(); varIt++, valueIt++)
        {
            hFile << *varIt << "=" << *valueIt << std::endl;
        }
    }
    hFile.close();
}
