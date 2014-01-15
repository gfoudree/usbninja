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

#include "authdrive.h"
#include <boost/range/algorithm.hpp>

AuthDrive::AuthDrive()
{
}

AuthDrive::AuthDrive(std::string _driveName, unsigned int _driveSize, std::string _notes)
{
    driveName = _driveName;
    driveSize = _driveSize;
    notes = _notes;
}

std::string AuthDrive::generateRandomString()
{
    byte pcbScratch[16*8];
    CryptoPP::AutoSeededX917RNG<CryptoPP::DES_EDE3> rng;
    rng.GenerateBlock(pcbScratch, 16*8);

    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(pcbScratch, sizeof(pcbScratch));
    encoder.MessageEnd();

    return output;
}

bool AuthDrive::logEntry()
{
    char sqlStmt[512];
    bool ret;
    Sql sql;
    sql.dbConnect((char*)Paths::getDatabasePath().c_str(), true);

    std::string notes = this->notes;
    boost::algorithm::trim(notes); //Clean up extra characters
    notes.erase(boost::remove_if(notes, boost::algorithm::is_any_of("\n\'\r\t")), notes.end());

    sprintf(sqlStmt, "INSERT INTO authDrives (dateAuthorized, serial, driveName, driveSize, notes) VALUES (\'%s\', \'%s\', \'%s\', %d, \'%s\');",
            this->date.c_str(), this->serial.c_str(), this->driveName.c_str(), this->driveSize, notes.c_str());
    ret = sql.dbExecSql(sqlStmt);
    sql.dbDisconnect();
    return ret;
}
