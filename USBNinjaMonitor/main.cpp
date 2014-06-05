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

#include "main.h"
#include "handler.h"
#include "traynotify.h"
#include "virusscan.h"

#define NIN_BALLOONUSERCLICK (WM_USER + 5)

boost::thread_group thrd_grp;
boost::mutex gMutex;

NOTIFYICONDATAA nid;
TrayNotify trayNotification;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArguement, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    char szClassName[] = "USBNinja";
    wchar_t szClassNameW[15];
    mbstowcs(szClassNameW, szClassName, sizeof(szClassName));

    /* Check if program is already running */
    SetLastError(0);
    CreateMutexA(0, FALSE, "Local\\$USBNINJA_DAEMON_MUTEX$");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ErrorLog::logErrorToFile("*INFO*", "USBNinja is already running...");
        MessageBoxA(NULL, "USBNinja is already running", "Error", MB_OK);
        exit(1);
    }

    wincl.hInstance = hInstance;
    wincl.lpszClassName = szClassNameW;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&wincl))
            return 0;
    hwnd = CreateWindowExA (
               0,
               szClassName,
               szClassName,
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT,
               CW_USEDEFAULT,
               544,
               375,
               HWND_DESKTOP,
               NULL,
               hInstance,
               NULL
               );
    ErrorLog::logErrorToFile("*INFO*", "USBNinja daemon started.");
    atexit(logQuitMessage);

    trayNotification.setWindow(hwnd);
    trayNotification.sendMessage("USBNinja daemon started.", "USBNinja");

    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    VirusScan vs;
    vs.lockFiles(vs.findFiles('E'));

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DEVICECHANGE:
        {
            PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR) lParam;
            if (wParam == DBT_DEVICEARRIVAL && pHdr->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME pHdrv = (PDEV_BROADCAST_VOLUME) pHdr;
                char driveLtr = UsbDevice::FirstDriveFromMask(pHdrv->dbcv_unitmask);

                thrd_grp.create_thread(boost::bind(threadHandler, driveLtr));

                trayNotification.sendMessage("Drive Inserted", "Alert");
            }
        }
        break;

    case WM_NOTIFYBUBBLECLICK:
    {
        /* Tray notification bubble clicked */
        if (lParam == NIN_BALLOONUSERCLICK)
        {

        }
    }
    break;

    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;

    default:
        return DefWindowProcA(hwnd, message, wParam, lParam);
    }
    return 0;
}

void logQuitMessage()
{
    ErrorLog::logErrorToFile("*INFO*", "USBNinja daemon stopped.");
    thrd_grp.join_all();
}
