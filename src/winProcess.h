#ifndef SRC_WINPROCESS_H_
#define SRC_WINPROCESS_H_

#include <string>
#include <Windows.h>

namespace winProcess
{
    bool FindProcessId(const std::string &processName, DWORD processIdArray[]);

    bool KillProcess(DWORD dwPid);

} // namespace winProcess

#endif // SRC_WINPROCESS_H_