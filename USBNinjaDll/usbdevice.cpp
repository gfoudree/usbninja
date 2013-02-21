#include "usbdevice.h"

UsbDevice::UsbDevice()
{
}

bool UsbDevice::GetDriveDeviceId(char drvLtr, std::string *deviceID)
{
    HKEY key;
    LONG regOpn = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\MountedDevices", 0, KEY_QUERY_VALUE, &key);

    if (regOpn == ERROR_SUCCESS)
    {
        char value[1024] = {0};
        char valueName[256] = {0};
        DWORD szValue = sizeof(value);
        std::string tempStr;

        strcpy(valueName, "\\DosDevices\\");
        valueName[strlen(valueName)] = drvLtr;
        strcat(valueName, ":");
        regOpn = RegQueryValueExA(key, valueName, NULL, NULL, (BYTE*)value, &szValue);
        if (regOpn != ERROR_SUCCESS)
        {
            RegCloseKey(key);
            return false;
        }
        RegCloseKey(key);

        for (int i = 0; i < 255; i++)
        {
            if (value[i] != '\0')
            {
                if (value[i] == '#')
                    tempStr += '\\';
                else if (value[i] == '{')
                    break;
                else
                    tempStr += value[i];
            }
        }
        *deviceID = strstr((char*)tempStr.c_str(), "USBSTOR");
        deviceID->erase(deviceID->size() -1);

        if (regOpn == ERROR_SUCCESS)
            return true;
        else
            return false;
    }
    else
    {
        RegCloseKey(key);
        return false;
    }
}

bool UsbDevice::GetFriendlyName(std::string deviceID, std::string *friendlyName)
{
    HKEY key;
    char keyName[512] = {0};
    strcpy(keyName, "SYSTEM\\CurrentControlSet\\Enum\\");
    strcat(keyName, (char*)deviceID.c_str());
    LONG regOpn = RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyName, 0, KEY_QUERY_VALUE, &key);
    if (regOpn == ERROR_SUCCESS)
    {
        char value[512];
        DWORD szValue = sizeof(value);
        regOpn = RegQueryValueExA(key, "FriendlyName", 0, NULL, (BYTE*)value, &szValue);
        if (regOpn != ERROR_SUCCESS)
        {
            RegCloseKey(key);
            return false;
        }
        RegCloseKey(key);

        *friendlyName += value;
        return true;
    }
    else
    {
        RegCloseKey(key);
        return false;
    }
}

bool UsbDevice::GetVolumeSerial(char drvLtr, std::string *serial)
{
    DWORD serialNum;
    if (GetVolumeInformationA(ltrtstr(drvLtr).c_str(), NULL, 0, &serialNum, NULL, NULL, NULL, 0) == 0)
        return false;
    else
    {
        *serial = toStr<DWORD>(serialNum);
        return true;
    }
}

bool UsbDevice::GetVolumeName(char drvLtr, std::string *name)
{
    char label[255];
    if (GetVolumeInformationA(ltrtstr(drvLtr).c_str(), label, sizeof(label), NULL, NULL, NULL, NULL, 0) == 0)
        return false;
    else
    {
        *name = toStr<>(label);
        return true;
    }
}

bool UsbDevice::GetVolumeSize(char drvLtr, unsigned int *volSize)
{
    ULARGE_INTEGER freeSpace, diskSpace;
    if(GetDiskFreeSpaceExA(ltrtstr(drvLtr).c_str(), &freeSpace, &diskSpace, NULL) == 0)
        return false;
    else
    {
        *volSize = diskSpace.QuadPart >> 20;
        return true;
    }
}

bool UsbDevice::GetVolumeLabel(char drvLtr, std::string *label)
{
    char labelBuf[MAX_PATH];
    DWORD dwRet;
    if (!GetVolumeInformationA(UsbDevice::ltrtstr(drvLtr).c_str(),
                               labelBuf, sizeof(labelBuf),
                               NULL, &dwRet, &dwRet, NULL, 0))
    {
        return false;
    }
    *label = labelBuf;
    return true;
}

bool UsbDevice::GetVolumeGUID(char drvLtr, std::string *GUID)
{
    char GUIDBuf[512];
    if (!GetVolumeNameForVolumeMountPointA(UsbDevice::ltrtstr(drvLtr).c_str(),
                                           GUIDBuf, sizeof(GUIDBuf)))
    {
        return false;
    }
    *GUID = GUIDBuf;
    return true;
}

char UsbDevice::FirstDriveFromMask(ULONG unitmask)
{
    char i;
    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1) break;
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}

template <class T>
inline std::string UsbDevice::toStr(T val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

std::string UsbDevice::ltrtstr(char driveLtr)
{
    std::string retVal;
    retVal.append(1, driveLtr);
    retVal.append(":\\");
    return retVal;
}
