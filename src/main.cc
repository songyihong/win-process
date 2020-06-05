#include "nan.h"
using namespace v8;

#include "winProcess.h"

namespace
{

    void FindProcess(const Nan::FunctionCallbackInfo<Value> &info)
    {
        bool isSucc;
        if (!info[0]->IsString())
        {
            Nan::ThrowTypeError("Bad argument");
            return;
        }

        std::string processName(*String::Utf8Value(info[0]));

        DWORD processIdArray[100];

        isSucc = winProcess::FindProcessId(processName, processIdArray);

        if (isSucc)
        {
            int len = 0;
            for (int i = 0; i < 100; i++)
            {
                if (!processIdArray[i])
                {
                    break;
                }
                len++;
            }
            Local<Array> res = Nan::New<Array>(0);
            for (int j = 0; j < len; j++)
            {
                Nan::Set(res, j, Nan::New(static_cast<uint32_t>(processIdArray[j])));
            }

            info.GetReturnValue().Set(res);
        }
        else
        {
            info.GetReturnValue().Set(Nan::New<Boolean>(isSucc));
        }
    }

    void KillProcess(const Nan::FunctionCallbackInfo<Value> &info)
    {
        if (!info[0]->IsString() && !info[0]->IsNumber())
        {
            Nan::ThrowTypeError("Bad argument");
            return;
        }
        bool isOk = winProcess::KillProcess(info[0]->Uint32Value());
        info.GetReturnValue().Set(Nan::New<Boolean>(isOk));
    }

    void Init(Handle<Object> exports)
    {
        Nan::SetMethod(exports, "killProcess", KillProcess);
        Nan::SetMethod(exports, "findProcess", FindProcess);
    }

} // namespace

NODE_MODULE(winProcess, Init)