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

#ifndef USBKEY_H
#define USBKEY_H

#include "usbbpb.h"

#include <zlib.h>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/format.hpp>
#include <sstream>


class UsbKey : public UsbBPB
{
public:
    char usbninjaSignature[5];

    __declspec(dllexport) static std::string generateCrc32(unsigned char *buf, unsigned int len);
    __declspec(dllexport) static std::string generateRandStr(const int len);
    __declspec(dllexport) static std::string generateTimestamp();

    __declspec(dllexport) UsbKey();
};

struct UsbKeyhdr
{
    char usbninjaSignature[5];
    char serialkey[25];
    char timestamp[12];
    char crc32[10];
};

#endif // USBKEY_H
