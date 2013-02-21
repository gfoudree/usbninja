#ifndef USBDEVICE_H
#define USBDEVICE_H

#define _WIN32_WINNT 0x601
#include <windows.h>
#include <iostream>
#include <sstream>

class UsbDevice
{
private:
    static std::string ltrtstr(char driveLtr);

public:

    static bool GetDriveDeviceId(char drvLtr, std::string *deviceID);
    static bool GetFriendlyName(std::string deviceID, std::string *friendlyName);
    static bool GetVolumeSerial(char drvLtr, std::string *serial);
    static bool GetVolumeName(char drvLtr, std::string *name);
    static bool GetVolumeSize(char drvLtr, unsigned int *volSize);
    static bool GetVolumeLabel(char drvLtr, std::string *label);
    static bool GetVolumeGUID(char drvLtr, std::string *GUID);
    static char FirstDriveFromMask(ULONG unitmask);

    template <class T>
    static inline std::string toStr(T val);

    UsbDevice();
};

#endif // USBDEVICE_H
