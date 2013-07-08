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

bool Service::StopServ(char* name)
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

bool Service::StartServ(char* name)
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

bool Service::ChkServ(char* name)
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

bool Service::InstallServ(char* name, char* desc, char* path)
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

bool Service::ChkProcess(char *name)
{
    wchar_t exeFile[50];
    mbstowcs(exeFile, name, strlen(name));

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return false;

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return false;
    }
    do
    {
        if (wcscmp(pe32.szExeFile, exeFile) == 0)
        {
            CloseHandle(hProcessSnap);
            return true;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return false;
}

bool Service::StartProcess(char *name)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);

    if (!CreateProcessA(name, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        ErrorLog::logErrorToFile("*WARNING*", "Unable to create process: ",
                                 ErrorLog::winErrToStr(GetLastError()));
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return false;
    }
    else
    {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    }
}

bool Service::StopProcess(char *name)
{
    DWORD pid = Service::getPID(name);
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProc == NULL)
    {
        ErrorLog::logErrorToFile("*WARNING*", "Unable to open process: ", name, " Error code: ",
                                 ErrorLog::winErrToStr(GetLastError()));
        return false;
    }

    if (TerminateProcess(hProc, 1) == 0)
    {
        ErrorLog::logErrorToFile("*WARNING*", "Unable to terminate process: ",
                                 ErrorLog::winErrToStr(GetLastError()));
        return false;
    }
    return true;
}

DWORD Service::getPID(char *name)
{
    wchar_t exeName[50];
    swprintf(exeName, L"%hs", name);
    HANDLE hProcessSnap;

    PROCESSENTRY32W pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        ErrorLog::logErrorToFile("*WARNING*", "Unable to create process snapshot: ",
                                 ErrorLog::winErrToStr(GetLastError()));
        return false;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return false;
    }

    do
    {
        if (wcscmp(exeName, pe32.szExeFile) == 0)
        {
            CloseHandle(hProcessSnap);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return 0;
}
