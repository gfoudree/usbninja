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

UsbBPB::UsbBPB()
{
}

BOOL UsbBPB::openDevice(char drvLtr)
{
    std::string drvLtrWinFmt = UsbDevice::ltrtCreateFilestr(drvLtr);
    hFile = CreateFileA(drvLtrWinFmt.c_str(),
                               GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL, OPEN_EXISTING, 0, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
        return TRUE;
    else
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Error opening device for raw read/write: ",
                                 ErrorLog::winErrToStr(GetLastError()));
        return FALSE;
    }
}

BOOL UsbBPB::readBPBCode32(unsigned char *buf)
{
    DWORD bRead;
    SetFilePointer(hFile, FAT32_BPB_BOOTCODE, NULL, FILE_BEGIN);
    BOOL res = ReadFile(hFile, buf, FAT32_BPB_BOOTCODE_LEN, &bRead, NULL);
    return res;
}

BOOL UsbBPB::writeBPBCode32(unsigned char *buf)
{
    char prevBPB[1024];
    if (!readDiskSector(prevBPB))
        return false;
    memcpy(&prevBPB[FAT32_BPB_BOOTCODE], buf, 512 - FAT32_BPB_BOOTCODE);
    if (!writeDiskSector(prevBPB))
        return false;
    return true;
}

BOOL UsbBPB::clearBPBCode32()
{
    unsigned char buf[FAT32_BPB_BOOTCODE_LEN];
    memset(buf, 0, FAT32_BPB_BOOTCODE_LEN);
    return writeBPBCode32(buf);
}

BOOL UsbBPB::readBPBCode16(unsigned char *buf)
{
    DWORD bRead;
    SetFilePointer(hFile, FAT16_BPB_BOOTCODE, NULL, FILE_BEGIN);
    BOOL res = ReadFile(hFile, buf, FAT16_BPB_BOOTCODE_LEN, &bRead, NULL);
    return res;
}

BOOL UsbBPB::writeBPBCode16(unsigned char *buf)
{
    char prevBPB[1024];
    if (!readDiskSector(prevBPB))
        return false;
    memcpy(&prevBPB[FAT16_BPB_BOOTCODE], buf, 512 - FAT16_BPB_BOOTCODE);
    if (!writeDiskSector(prevBPB))
        return false;
    return true;
}

BOOL UsbBPB::clearBPBCode16()
{
    unsigned char buf[FAT16_BPB_BOOTCODE_LEN];
    memset(buf, 0, FAT16_BPB_BOOTCODE_LEN);
    return writeBPBCode16(buf);
}

BOOL UsbBPB::readDiskSector(char *readBuf)
{
    DWORD cb, rb;
    if (!DeviceIoControl(hFile, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &cb, NULL))
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Error locking volume ", ErrorLog::winErrToStr(GetLastError()));
        return FALSE;
    }

    if (!ReadFile(hFile, readBuf, 512*1, &rb, 0))
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Error reading from volume ", ErrorLog::winErrToStr(GetLastError()));
        return FALSE;
    }
    DeviceIoControl(hFile, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &cb, NULL);
    SetFilePointer(hFile, 0, 0, FILE_BEGIN);
    return TRUE;
}

BOOL UsbBPB::writeDiskSector(char *writeBuf)
{
    DWORD cb, wb;
    if (!DeviceIoControl(hFile, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &cb, NULL))
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Error locking volume ", ErrorLog::winErrToStr(GetLastError()));
        return FALSE;
    }

    if (!WriteFile(hFile, writeBuf, 512*1, &wb, 0))
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Error writing to volume ", ErrorLog::winErrToStr(GetLastError()));
        return FALSE;
    }
    DeviceIoControl(hFile, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &cb, NULL);
    return TRUE;
}

UsbBPB::~UsbBPB()
{
    CloseHandle(hFile);
}
