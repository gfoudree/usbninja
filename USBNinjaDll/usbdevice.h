#ifndef USBDEVICE_H
#define USBDEVICE_H

#define _WIN32_WINNT 0x601
#include <windows.h>
#include <iostream>
#include <sstream>
#include "errorlog.h"

class UsbDevice
{
private:
    static std::string ltrtstr(char driveLtr);

public:

    __declspec(dllexport) static bool GetDriveDeviceId(char drvLtr, std::string *deviceID);
    __declspec(dllexport) static bool GetFriendlyName(std::string deviceID, std::string *friendlyName);
    __declspec(dllexport) static bool GetVolumeSerial(char drvLtr, std::string *serial);
    __declspec(dllexport) static bool GetVolumeName(char drvLtr, std::string *name);
    __declspec(dllexport) static bool GetVolumeSize(char drvLtr, unsigned int *volSize);
    __declspec(dllexport) static bool GetVolumeLabel(char drvLtr, std::string *label);
    __declspec(dllexport) static bool GetVolumeGUID(char drvLtr, std::string *GUID);
    __declspec(dllexport) static char FirstDriveFromMask(ULONG unitmask);

    template <class T>
    __declspec(dllexport) static inline std::string toStr(T val);

    __declspec(dllexport) UsbDevice();
};

#endif // USBDEVICE_H
