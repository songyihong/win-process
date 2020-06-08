#include "nan.h"
using namespace v8;

#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <ShellAPI.h>
#include <stdio.h>
#include <psapi.h>
#include <string.h>

namespace
{

    void FindProcessId(const Nan::FunctionCallbackInfo<Value> &info)
    {
        if (!info[0]->IsString())
        {
            Nan::ThrowTypeError("Bad argument");
            return;
        }

        std::string processName(*String::Utf8Value(info[0]));

        PROCESSENTRY32 processInfo;
        processInfo.dwSize = sizeof(processInfo);

        HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (processesSnapshot == INVALID_HANDLE_VALUE)
        {
            info.GetReturnValue().Set(Nan::New<Boolean>(false));
        }
        else
        {
            int i = 0;
            Local<Array> res = Nan::New<Array>(0);
            Process32First(processesSnapshot, &processInfo);
            if (!processName.compare(processInfo.szExeFile))
            {
                Nan::Set(res, i, Nan::New(static_cast<uint32_t>(processInfo.th32ProcessID)));
                i += 1;
            }

            while (Process32Next(processesSnapshot, &processInfo))
            {
                if (!processName.compare(processInfo.szExeFile))
                {
                    Nan::Set(res, i, Nan::New(static_cast<uint32_t>(processInfo.th32ProcessID)));
                    i += 1;
                }
            }

            CloseHandle(processesSnapshot);
            info.GetReturnValue().Set(res);
        }
    }

    void KillProcess(const Nan::FunctionCallbackInfo<Value> &info)
    {
        if (!info[0]->IsString() && !info[0]->IsNumber())
        {
            Nan::ThrowTypeError("Bad argument");
            return;
        }
        bool isOk;
        HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION | // Required by Alpha
                                            PROCESS_CREATE_THREAD |                     // For CreateRemoteThread
                                            PROCESS_VM_OPERATION |                      // For VirtualAllocEx/VirtualFreeEx
                                            PROCESS_VM_WRITE,                           // For WriteProcessMemory);
                                        FALSE, info[0]->Uint32Value());
        if (killHandle == NULL)
        {
            isOk = false;
        }
        else
        {
            TerminateProcess(killHandle, 0);
            isOk = true;
        }
        info.GetReturnValue().Set(Nan::New<Boolean>(isOk));
    }

    void FindProcessName(const Nan::FunctionCallbackInfo<Value> &info)
    {
        if (!info[0]->IsString() && !info[0]->IsNumber())
        {
            Nan::ThrowTypeError("Bad argument");
            return;
        }

        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                          PROCESS_VM_READ,
                                      FALSE, info[0]->Uint32Value());
        if (hProcess == NULL)
        {
            info.GetReturnValue().Set(Nan::New<Boolean>(true));
        }
        else
        {
            TCHAR szProcessName[MAX_PATH];

            if (GetModuleFileNameEx(hProcess, 0, szProcessName, MAX_PATH))
            {
                std::basic_string<TCHAR> pathName = szProcessName;
                CloseHandle(hProcess);
                char ch = '\\';
                std::string sTemp = pathName;
                std::replace(sTemp.begin(), sTemp.end(), '/', '\\');
                std::string::size_type pos = sTemp.find_last_of(ch);

                if (pos != std::string::npos)
                {
                    std::string sAppName = pathName.substr(pos + 1);
                    info.GetReturnValue().Set(Nan::New<String>(sAppName).ToLocalChecked());
                }
                else
                {
                    info.GetReturnValue().Set(Nan::New<Boolean>(false));
                }
            }
            else
            {
                info.GetReturnValue().Set(Nan::New<Boolean>(false));
            }
        }
    }

    void Init(Handle<Object> exports)
    {
        Nan::SetMethod(exports, "killProcess", KillProcess);
        Nan::SetMethod(exports, "findProcess", FindProcessId);
        Nan::SetMethod(exports, "findProcessId", FindProcessId);
        Nan::SetMethod(exports, "findProcessName", FindProcessName);
    }

} // namespace

NODE_MODULE(winProcess, Init)