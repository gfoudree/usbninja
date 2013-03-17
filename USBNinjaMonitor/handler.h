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
