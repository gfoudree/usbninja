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
 #include "settings.h"

Settings::Settings()
{
}

std::string Settings::queryXml(const char *xquery, const char *xmlFile)
{
    pugi::xml_document doc;
    pugi::xml_parse_result res = doc.load_file(xmlFile);
    if (!res)
    {
        ErrorLog::logErrorToFile("Unable to parse/open xml file: ", (char*)xmlFile, " error code: ", (char*)res.description());
        return "";
    }
    pugi::xpath_query query(xquery);
    return query.evaluate_string(doc);
}
