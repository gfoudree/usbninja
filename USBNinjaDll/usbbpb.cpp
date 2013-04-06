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

#include "usbbpb.h"

usbBPB::usbBPB()
{
}

BOOL usbBPB::openDevice()
{
    hFile = CreateFileA("C:\\users\\grant\\desktop\\test.img",
                               GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL, OPEN_EXISTING, 0, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
        return TRUE;
    else
        return FALSE;
}

BOOL usbBPB::readBPBCode32(unsigned char *buf)
{
    DWORD bRead;
    SetFilePointer(hFile, BPB_BOOTCODE, NULL, FILE_BEGIN);
    BOOL res = ReadFile(hFile, buf, BPB_BOOTCODE_LEN, &bRead, NULL);
    return res;
}

BOOL usbBPB::writeBPBCode32(unsigned char *buf)
{
    DWORD bWrite;
    SetFilePointer(hFile, BPB_BOOTCODE, NULL, FILE_BEGIN);
    BOOL res = WriteFile(hFile, buf, BPB_BOOTCODE_LEN, &bWrite, NULL);
    return res;
}

BOOL usbBPB::clearBPBCode32()
{
    unsigned char buf[BPB_BOOTCODE_LEN];
    memset(buf, 0, BPB_BOOTCODE_LEN);
    return writeBPBCode32(buf);
}

BOOL usbBPB::readBPBCode16(unsigned char *buf)
{
    DWORD bRead;
    SetFilePointer(hFile, FAT16_BPB_BOOTCODE, NULL, FILE_BEGIN);
    BOOL res = ReadFile(hFile, buf, FAT16_BPB_BOOTCODE_LEN, &bRead, NULL);
    return res;
}

BOOL usbBPB::writeBPBCode16(unsigned char *buf)
{
    DWORD bWrite;
    SetFilePointer(hFile, FAT16_BPB_BOOTCODE, NULL, FILE_BEGIN);
    BOOL res = WriteFile(hFile, buf, FAT16_BPB_BOOTCODE_LEN, &bWrite, NULL);
    return res;
}

BOOL usbBPB::clearBPBCode16()
{
    unsigned char buf[FAT16_BPB_BOOTCODE_LEN];
    memset(buf, 0, FAT16_BPB_BOOTCODE_LEN);
    return writeBPBCode16(buf);
}

usbBPB::~usbBPB()
{
    CloseHandle(hFile);
}
