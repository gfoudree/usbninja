#include <iostream>
#include <windows.h>
#include <dbt.h>
#include <stdlib.h>
#include <winsvc.h>
#include <../USBNinjaDll/usbdevice.h>
#include <../USBNinjaDll/sql.h>
#include <../USBNinjaDll/errorlog.h>

using namespace std;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArguement, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    char szClassName[] = "USBNinja";
    wchar_t szClassNameW[15];
    mbstowcs(szClassNameW, szClassName, sizeof(szClassName));

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
                Sql sql;
                sql.dbConnect("C:\\users\\grant\\desktop\\log.db");
                sql.dbDisconnect();
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcA(hwnd, message, wParam, lParam);
    }
    return 0;
}
