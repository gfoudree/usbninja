#ifndef MAIN_H
#define MAIN_H

#define _WIN32_WINNT 0x0601
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <dbt.h>
#include <stdlib.h>
#include <winsvc.h>
#include <string.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <../USBNinjaDll/usbdevice.h>
#include <../USBNinjaDll/sql.h>
#include <../USBNinjaDll/errorlog.h>
#include <../USBNinjaDll/service.h>

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void logQuitMessage();

#endif // MAIN_H
