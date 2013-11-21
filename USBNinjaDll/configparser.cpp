#include "configparser.h"

int ConfigParser::findPos(std::string varStr)
{
    std::vector<std::string>::iterator it;
    it = std::find(var.begin(), var.end(), varStr);
    if (it != var.end())
        return std::distance(var.begin(), it);
    else
        return -1;
}

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
    int pos = findPos(varStr);
    if (pos == -1)
        return "";
    else
        return value.at(pos);
}

std::string ConfigParser::getData()
{
    return configFileData;
}

void ConfigParser::setValue(std::string varStr, std::string valueStr)
{
    int pos = findPos(varStr);
    if (pos != -1)
        value[pos] = valueStr;
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

sqlSettings ConfigParser::getSqlSettings()
{
    sqlSettings sql;

    ConfigParser configParser((char*)Paths::getConfigPath().c_str());
    sql.ip = configParser.getValue("ip");
    sql.username = configParser.getValue("username");
    sql.password = configParser.getValue("password");
    sql.database = configParser.getValue("database");
    sql.port = atoi((char*)configParser.getValue("port").c_str());
    return sql;
}
