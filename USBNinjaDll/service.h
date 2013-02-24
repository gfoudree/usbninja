#ifndef SERVICE_H
#define SERVICE_H

#define _WIN32_WINNT 0x601
#include <windows.h>

__declspec(dllexport) bool InstallServ(char* name, char* desc, char* path);
__declspec(dllexport) bool StopServ(char* name);
__declspec(dllexport) bool StartServ(char* name);
__declspec(dllexport) bool ChkServ(char* name);

#endif // SERVICE_H
