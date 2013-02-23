#ifndef SERVICE_H
#define SERVICE_H

#define _WIN32_WINNT 0x601
#include <windows.h>

bool InstallServ(char* name, char* desc, char* path);
bool StopServ(char* name);
bool StartServ(char* name);
bool ChkServ(char* name);

#endif // SERVICE_H
