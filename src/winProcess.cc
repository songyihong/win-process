#include "winProcess.h"

#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <ShellAPI.h>

namespace winProcess
{
    bool KillProcess(DWORD dwPid)
    {
        HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION | // Required by Alpha
                                            PROCESS_CREATE_THREAD |                     // For CreateRemoteThread
                                            PROCESS_VM_OPERATION |                      // For VirtualAllocEx/VirtualFreeEx
                                            PROCESS_VM_WRITE,                           // For WriteProcessMemory);
                                        FALSE, dwPid);
        if (killHandle == NULL)
            return false;
        TerminateProcess(killHandle, 0);
        return true;
    }

    bool FindProcessId(const std::string &processName, DWORD processIdArray[])
    {
        int i = 0;
        PROCESSENTRY32 processInfo;
        processInfo.dwSize = sizeof(processInfo);

        HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (processesSnapshot == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        Process32First(processesSnapshot, &processInfo);
        if (!processName.compare(processInfo.szExeFile))
        {
            processIdArray[i] = processInfo.th32ProcessID;
            i += 1;
        }

        while (Process32Next(processesSnapshot, &processInfo))
        {
            if (!processName.compare(processInfo.szExeFile))
            {
                processIdArray[i] = processInfo.th32ProcessID;
                i += 1;
            }
        }

        CloseHandle(processesSnapshot);
        return true;
    }
} // namespace winProcess