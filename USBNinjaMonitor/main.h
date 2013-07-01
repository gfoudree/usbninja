#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <windows.h>
#include <dbt.h>
#include <stdlib.h>
#include <winsvc.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <../USBNinjaDll/usbdevice.h>
#include <../USBNinjaDll/sql.h>
#include <../USBNinjaDll/errorlog.h>

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void logQuitMessage();

#endif // MAIN_H
