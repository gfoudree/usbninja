#include "traynotify.h"

TrayNotify::TrayNotify()
{

}

TrayNotify::~TrayNotify()
{
    Shell_NotifyIconA(NIM_DELETE, &nid);
}

void TrayNotify::sendMessage(char *message, char *title)
{
    strcpy(nid.szInfo, message);
    strcpy(nid.szInfoTitle, title);
    Shell_NotifyIconA(NIM_MODIFY, &nid);
}

void TrayNotify::setWindow(HWND hWindow)
{
    hwnd = hWindow;
    nid.cbSize = sizeof(NOTIFYICONDATAA);
    nid.hWnd = hwnd;
    nid.guidItem = usbninjaGUID;
    nid.uVersion = NOTIFYICON_VERSION_4;
    nid.uCallbackMessage = WM_NOTIFYBUBBLECLICK;
    nid.dwInfoFlags = 0x00000001; //Information Icon for balloon popup
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    strcpy(nid.szTip, "USBNinja Daemon");
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO | NIF_GUID;

    Shell_NotifyIconA(NIM_ADD, &nid);
}

void TrayNotify::getMessage(char *message, char *title)
{
    strcpy(message, nid.szInfo);
    strcpy(title, nid.szInfoTitle);
}
