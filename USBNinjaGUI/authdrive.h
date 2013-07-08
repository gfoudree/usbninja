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

#ifndef AUTHDRIVE_H
#define AUTHDRIVE_H

#include <cryptopp/osrng.h>
#include <cryptopp/des.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <stdio.h>

#include <../../USBNinjaDll/errorlog.h>
#include <../../USBNinjaDll/sql.h>
#include <../../USBNinjaDll/paths.h>

class AuthDrive : public ErrorLog //To get dateAndTime();
{
public:
    std::string driveName;
    unsigned int driveSize;
    std::string notes;
    std::string date;
    std::string serial;

    static std::string generateRandomString();
    bool logEntry();

    AuthDrive();
    AuthDrive(std::string _driveName, unsigned int _driveSize, std::string _notes);
};

#endif // AUTHDRIVE_H
