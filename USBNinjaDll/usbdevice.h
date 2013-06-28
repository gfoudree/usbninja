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
 #ifndef USBDEVICE_H
#define USBDEVICE_H

#define _WIN32_WINNT 0x601
#include <windows.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "errorlog.h"

struct DriveInfo;

class UsbDevice
{
public:

    __declspec(dllexport) static bool GetDriveDeviceId(char drvLtr, std::string *deviceID);
    __declspec(dllexport) static bool GetFriendlyName(std::string deviceID, std::string *friendlyName);
    __declspec(dllexport) static bool GetVolumeSerial(char drvLtr, std::string *serial);
    __declspec(dllexport) static bool GetVolumeName(char drvLtr, std::string *name);
    __declspec(dllexport) static bool GetVolumeSize(char drvLtr, unsigned int *volSize);
    __declspec(dllexport) static bool GetVolumeLabel(char drvLtr, std::string *label);
    __declspec(dllexport) static bool GetVolumeGUID(char drvLtr, std::string *GUID);
    __declspec(dllexport) static bool GetVolumeFilesystem(char drvLtr, std::string *fileSystem);
    __declspec(dllexport) static char FirstDriveFromMask(ULONG unitmask);
    __declspec(dllexport) static std::vector<char> getUSBDrives(DWORD *numDrives);
    __declspec(dllexport) static bool getDriveInfo(DriveInfo *pDrvInfo, std::string drive);
	
    template <class T>
    __declspec(dllexport) static inline std::string toStr(T val);
    __declspec(dllexport) static std::string ltrtstr(char driveLtr);
    __declspec(dllexport) UsbDevice();
};


struct DriveInfo
{
    ULONGLONG tSpace;   /* Total disk space */
    ULONGLONG fSpace;   /* Total free space */
    char devName[MAX_PATH]; /* Device name */
    char devFs[15];   /* File system type */
};

struct DriveInfoS
{
    int diskSize;
    std::string driveName;
    std::string driveFilesystem;
};

#endif // USBDEVICE_H
