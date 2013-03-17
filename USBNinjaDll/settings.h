/*
 * Copyright (C) by Grant Foudree <grant907@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */
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
