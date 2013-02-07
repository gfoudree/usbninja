#ifndef USBOPS_H
#define USBOPS_H

#include <windows.h>
#include <winioctl.h>
#include <stdio.h>

class UsbOps
{
protected:
    HANDLE hVolume;
    DWORD dwRetBytes;
public:
    void lockUSB(char driveLtr);
    void unlockUSB();
    UsbOps();
    ~UsbOps();
};

#endif // USBOPS_H
