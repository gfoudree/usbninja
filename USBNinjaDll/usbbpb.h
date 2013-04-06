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

#ifndef USBBPB_H
#define USBBPB_H

#include <windows.h>

#define BPB_BOOTCODE 0x5A
#define BPB_BOOTCODE_LEN 0x1A6
#define FAT16_BPB_BOOTCODE 0x3E
#define FAT16_BPB_BOOTCODE_LEN 0x1C2

class usbBPB
{
protected:
    HANDLE hFile;
public:
    BOOL openDevice();
    BOOL readBPBCode32(unsigned char *buf);
    BOOL writeBPBCode32(unsigned char *buf);
    BOOL clearBPBCode32();
    BOOL readBPBCode16(unsigned char *buf);
    BOOL writeBPBCode16(unsigned char *buf);
    BOOL clearBPBCode16();

    ~usbBPB();
    usbBPB();
};

#endif // USBBPB_H
