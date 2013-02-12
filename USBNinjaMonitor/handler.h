#ifndef HANDLER_H
#define HANDLER_H

#include <boost/thread.hpp>
#include <windows.h>
#include <winioctl.h>
#include <iostream>
#include <../USBNinjaDll/usbdevice.h>
#include <../USBNinjaDll/settings.h>
#include <../USBNinjaDll/sql.h>

void threadHandler(char driveLtr);


#endif // HANDLER_H
