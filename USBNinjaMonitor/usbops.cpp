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

    HANDLE hVolume = CreateFileA(driveFileName, GENERIC_READ | GENERIC_WRITE,
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
