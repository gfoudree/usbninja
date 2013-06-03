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
}

unsigned long UsbKey::generateCrc32(unsigned char *buf, unsigned int len)
{
    unsigned long crc = crc32(0, buf, len);
    return crc;
}

std::string UsbKey::generateRandStr(const int len = 25)
{
    std::string randStr;
    std::string chars(
            "abcdefghijklmnopqrstuvwxyz"
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
