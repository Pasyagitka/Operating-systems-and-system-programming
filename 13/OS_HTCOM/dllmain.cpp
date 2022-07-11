// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <fstream>
#include "DllInstall.h"
//#define SEQHT LONG __XXCSeqHT=InterlockedIncrement(&SeqHT)
//#define LOGHT(x,y) LogHT<<__XXCSeqHT<<":"<<(x)<<(y)<<std::endl
//


HMODULE hmodule;
LONG Seq = 0;
std::fstream LogCOM;

ULONG g_Components = 0;
ULONG g_ServerLocks = 0;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            hmodule = hModule;
            LogCOM.open("d:\\logCOMHT.txt", std::ios_base::out);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            LogCOM.close();
            break;
    }
    return TRUE;
}


