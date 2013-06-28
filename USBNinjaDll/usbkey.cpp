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

#include "usbkey.h"

UsbKey::UsbKey()
{
    strncpy(usbninjaSignature, "NINJA", 5);
}

std::string UsbKey::generateCrc32(unsigned char *buf, unsigned int len)
{
    std::stringstream crcstr;
    unsigned long crc;
    crc = crc32(0, buf, len);

    crcstr << crc;
    return crcstr.str();
}

std::string UsbKey::generateRandStr(const int len = 25)
{
    std::string randStr;
    std::string chars(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "1234567890");
    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, chars.size() -1);
    for (int i = 0; i < len; i++)
    {
        randStr += chars[index_dist(rng)];
    }
    return randStr;
}

std::string UsbKey::generateTimestamp()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    std::stringstream timestampStr;
    timestampStr << timeinfo->tm_mon << timeinfo->tm_mday << timeinfo->tm_year;
    timestampStr << timeinfo->tm_hour << timeinfo->tm_min;

    return timestampStr.str();
}
