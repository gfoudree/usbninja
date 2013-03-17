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
 
#include "usbops.h"

UsbOps::UsbOps()
{
}
UsbOps::~UsbOps()
{
    CloseHandle(hVolume);
}

void UsbOps::lockUSB(char driveLtr)
{
    char driveFileName[10];
    sprintf(driveFileName, "\\\\.\\%c:", driveLtr);

    hVolume = CreateFileA(driveFileName, GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL,
                               OPEN_EXISTING,
                               0,
                               NULL);
    if (hVolume == INVALID_HANDLE_VALUE)
    {
        //log error
    }

    for (int i = 0; i < 20; i++)    //Try to lock it multiple times
    {
        if (DeviceIoControl(hVolume, FSCTL_LOCK_VOLUME,
                            NULL, 0, NULL, 0, &dwRetBytes, NULL))
            break;
        Sleep(1000);    //1 second pause between attempts
    }
}

void UsbOps::unlockUSB()
{
    for (int i = 0; i < 20; i++)
    {
        if (DeviceIoControl(hVolume, FSCTL_UNLOCK_VOLUME,
                            NULL, 0, NULL, 0, &dwRetBytes, NULL))
            break;
        Sleep(1000);    //1 second pause between attempts
    }
    CloseHandle(hVolume);
}

void UsbOps::ejectUSB()
{
    if (!dismountVolume())
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to dismount USB volume: ", ErrorLog::winErrToStr(GetLastError()));
    if (!preventRemovalOfVolume())
        ErrorLog::logErrorToFile("Unable to set USB drive to \"safe to remove\": ", ErrorLog::winErrToStr(GetLastError()));
    if (!autoEjectVolume())
        ErrorLog::logErrorToFile("*CRITICAL*", "Error ejecting USB volume: ", ErrorLog::winErrToStr(GetLastError()));
    CloseHandle(hVolume);
}

bool UsbOps::dismountVolume()
{
    DWORD bRet;
    return DeviceIoControl(hVolume, FSCTL_DISMOUNT_VOLUME, NULL, 0, NULL, 0, &bRet, NULL);
}

bool UsbOps::preventRemovalOfVolume()
{
    DWORD bRet;
    PREVENT_MEDIA_REMOVAL pmrBuf;
    pmrBuf.PreventMediaRemoval = FALSE;
    return DeviceIoControl(hVolume, IOCTL_STORAGE_MEDIA_REMOVAL, &pmrBuf,
                           sizeof(PREVENT_MEDIA_REMOVAL), NULL, 0, &bRet, NULL);
}

bool UsbOps::autoEjectVolume()
{
    DWORD bRet;
    return DeviceIoControl(hVolume, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0,
                           NULL, 0, &bRet, NULL);
}
