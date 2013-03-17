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
 #include "service.h"

bool StopServ(char* name)
{
    SC_HANDLE scm, serv;
    SERVICE_STATUS serv_stat;

    scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
    serv = OpenServiceA(scm, name, SERVICE_ALL_ACCESS);
    ControlService(serv, SERVICE_CONTROL_STOP, &serv_stat);
    if (GetLastError() == 0)
    {
        CloseServiceHandle(scm);
        CloseServiceHandle(serv);
        return true;
    }
    else
    {
        CloseServiceHandle(scm);
        CloseServiceHandle(serv);
        return false;
    }
}

bool StartServ(char* name)
{
    SC_HANDLE scm, serv;
    scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
    serv = OpenServiceA(scm, name, SERVICE_ALL_ACCESS);
    StartService(serv, 0, NULL);

    if (GetLastError() == 0)
    {
        CloseServiceHandle(scm);
        CloseServiceHandle(serv);
        return true;
    }
    else
    {
        CloseServiceHandle(scm);
        CloseServiceHandle(serv);
        return false;
    }
}

bool ChkServ(char* name)
{
    SC_HANDLE scm, serv;
    _SERVICE_STATUS servstat;
    scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
    serv = OpenServiceA(scm, name, SERVICE_ALL_ACCESS);
    ControlService(serv, SERVICE_CONTROL_INTERROGATE, &servstat);
    if (servstat.dwCurrentState == SERVICE_STOPPED)
    {
        CloseServiceHandle(scm);
        CloseServiceHandle(serv);
        return false;
    }
    else
    {
        CloseServiceHandle(scm);
        CloseServiceHandle(serv);
        return true;
    }
}

bool InstallServ(char* name, char* desc, char* path)
{
    SC_HANDLE scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
    CreateServiceA(scm, name, desc, SERVICE_ALL_ACCESS,
                  SERVICE_WIN32_OWN_PROCESS,
                  SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
                  path, 0, 0, 0, 0, 0);
    if (GetLastError() == 0)
    {
        CloseServiceHandle(scm);
        return true;
    }
    else
    {
        CloseServiceHandle(scm);
        return false;
    }
}
