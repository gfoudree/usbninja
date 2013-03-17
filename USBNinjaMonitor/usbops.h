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
 #ifndef USBOPS_H
#define USBOPS_H

#define _WIN32_WINNT 0x601
#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <../USBNinjaDll/errorlog.h>

class UsbOps
{
protected:
    HANDLE hVolume;
    DWORD dwRetBytes;
    bool dismountVolume();
    bool preventRemovalOfVolume();
    bool autoEjectVolume();

public:
    void lockUSB(char driveLtr);
    void unlockUSB();
    void ejectUSB();
    UsbOps();
    ~UsbOps();
};

#endif // USBOPS_H
