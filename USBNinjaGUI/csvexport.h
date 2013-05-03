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

#ifndef CSVEXPORT_H
#define CSVEXPORT_H

#include <../../USBNinjaDll/sql.h>
#include <iostream>
#include <fstream>

class CSVExport
{
public:
    std::string csvDataStr;

    std::string csvData();
    bool writeData(char *filePath);

    CSVExport();
};

#endif // CSVEXPORT_H
