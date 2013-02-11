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
