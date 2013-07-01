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
#ifndef SERVICE_H
#define SERVICE_H

#define _WIN32_WINNT 0x601
#include <windows.h>
#include <tlhelp32.h>
#include "errorlog.h"

class Service
{
public:

    __declspec(dllexport) static bool InstallServ(char* name, char* desc, char* path);
    __declspec(dllexport) static bool StopServ(char* name);
    __declspec(dllexport) static bool StartServ(char* name);
    __declspec(dllexport) static bool ChkServ(char* name);
    __declspec(dllexport) static bool StartProcess(char *name);
    __declspec(dllexport) static bool StopProcess(char* name);
    __declspec(dllexport) static bool ChkProcess(char *name);
    __declspec(dllexport) static DWORD getPID(char *name);

};

#endif // SERVICE_H
