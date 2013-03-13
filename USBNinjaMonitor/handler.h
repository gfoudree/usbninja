#ifndef HANDLER_H
#define HANDLER_H

#define _WIN32_WINNT 0x601
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <windows.h>
#include <winioctl.h>
#include <iostream>
#include <../USBNinjaDll/usbdevice.h>
#include <../USBNinjaDll/settings.h>
#include <../USBNinjaDll/sql.h>
#include <../USBNinjaDll/accesslog.h>
#include "usbops.h"

void threadHandler(char driveLtr);


#endif // HANDLER_H
