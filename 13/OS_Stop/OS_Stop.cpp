using namespace std;

#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include "../OS_HTCOM/HT.h"
#include <string.h>

#include <iostream>
#include "../OS_HTAPI/HashTableAPI.h"
using namespace HT;

#pragma comment(lib,"../Release/OS_HTAPI.lib")


void KillProcessByName(const wchar_t* filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);

    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (wcscmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

int main(int argc, char* argv[])
{
    char* fileName = (char*)"D:\\create.txt";

    HTHANDLE* HT = NULL;
    if (HTAPI::OpenApi())
    {
        if ((HT = HTAPI::OpenShared(fileName)) == NULL) throw "error while creating a ht";
        KillProcessByName(L"OS_Start.exe");
        KillProcessByName(L"OS_HT_Insert.exe");
        KillProcessByName(L"OS_HT_Update.exe");
        KillProcessByName(L"OS_HT_Delete.exe");
        HTAPI::Close(HT);
       
        if (HTAPI::CloseApi() == false) printf("error with close api\n");
        system("pause");
    }
    else
    {
        printf("error with open api\n");
    }
    return 0;
}