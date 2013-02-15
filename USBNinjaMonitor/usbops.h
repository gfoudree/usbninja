#ifndef USBOPS_H
#define USBOPS_H

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
