#include "paths.h"

std::string Paths::expandVariable(char *variable)
{
    char buf[MAX_PATH + 1];
    ExpandEnvironmentStringsA(variable, buf, sizeof(buf));
    return buf;
}

std::string Paths::getLogPath()
{
    std::string path = Paths::expandVariable("%appdata%");
    path.append("\\UsbNinja\\log.txt");
    return path;
}

std::string Paths::getDatabasePath()
{
    std::string path = Paths::expandVariable("%appdata%");
    path.append("\\UsbNinja\\drives.db");
    return path;
}
