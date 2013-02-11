#include "handler.h"

#include <iostream>
void threadHandler(char driveLtr)
{
    Settings set;
    std::cout << set.queryXml("/person/name") << "aa";
}
