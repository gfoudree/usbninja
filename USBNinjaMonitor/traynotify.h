#ifndef TRAYNOTIFY_H
#define TRAYNOTIFY_H

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#define _WIN32_IE 0x0601
#define WM_NOTIFYBUBBLECLICK (WM_APP + 100)
#define UsbIcon 110

#include <windows.h>
#include <Shellapi.h>
#include <Commctrl.h>

// {A6ECF816-8278-4613-B26B-D775FB57B02E}
static const GUID usbninjaGUID =
{ 0xa6ecf816, 0x8278, 0x4613, { 0xb2, 0x6b, 0xd7, 0x75, 0xfb, 0x57, 0xb0, 0x2e } };

class TrayNotify
{
protected:
    NOTIFYICONDATAA nid;
    HWND hwnd;
    HINSTANCE hInstance;

public:
    void setWindow(HWND hWindow);
    void sendMessage(char *message, char *title);
    void getMessage(char *message, char *title);
    void setHoverMessage(char *message);
    void setHInstance(HINSTANCE hInst);

    TrayNotify();
    ~TrayNotify();
};

#endif // TRAYNOTIFY_H
