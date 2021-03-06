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

#include "csvexport.h"
#include <boost/format.hpp>

CSVExport::CSVExport()
{
}

std::string CSVExport::csvData()
{
    std::string retVal = CSVExport::generateCSVHeader();

    std::vector<logUSB> usb;
    Sql sql;
    sql.dbConnect((char*)Paths::getDatabasePath().c_str(), false);
    sql.queryLog(&usb);
    sql.dbDisconnect();

    std::vector<logUSB>::iterator it = usb.begin();
    while (it != usb.end())
    {
        boost::format format = boost::format("%1%,%2%,%3%,%4%,%5%,%6%,%7%,%8%,%9%,%10%\n") % \
                                    (int)it->accepted % it->date % it->user % it->driveLetter % \
                                    it->driveName % it->driveLabel % it->driveSize % \
                                    it->driveSerial % it->driveGUID % it->usbninjaSerial;
        retVal.append(format.str());
        it++;
    }
    csvDataStr = retVal;
    return retVal;
}

bool CSVExport::writeData(char *filePath)
{
    if (strlen(filePath) < 2)
        return true;

    std::ofstream hFile;
    hFile.open(filePath);
    if (hFile.is_open())
    {
        hFile << csvDataStr;
        hFile.close();
        return true;
    }
    else
    {
        hFile.close();
        return false;
    }
}

std::string CSVExport::generateCSVHeader()
{
    std::stringstream header;
    header << "#Generated by USBNinja at " << ErrorLog::dateAndTime() << ".\n#CSV dump of USB logs.\n";
    return header.str();
}
