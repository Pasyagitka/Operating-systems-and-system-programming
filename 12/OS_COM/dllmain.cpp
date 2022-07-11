﻿// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <fstream>
#include "INSTALL.h"
#include "REGISTRY.h"
#include "SEQLOG.h"
#define SEQ LONG __XXCSeq=InterlockedIncement(&Seq)
#define LOG(x,y) LogCOM<<__XXCSeq<<":"<<x<<y<<std::endl

HMODULE hmodule;
LONG Seq = 0;
std::fstream LogCOM;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            hmodule = hModule;
            LogCOM.open("d:\\logCOM.txt", std::ios_base::out);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH: LogCOM.close(); break;
        break;
    }
    return TRUE;
}