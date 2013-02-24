#ifndef SETTINGS_H
#define SETTINGS_H

#include <pugixml.hpp>
#include <iostream>

#include "errorlog.h"

class Settings
{
public:
    __declspec(dllexport) static std::string queryXml(const char *xquery, const char *xmlFile = "settings.xml");
    __declspec(dllexport) Settings();
};


#endif // SETTINGS_H
