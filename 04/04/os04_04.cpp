#include <Windows.h>
#include <iostream>

DWORD WINAPI OS04_04_T1() 
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 1; i <= 50; i++) 
    {
        std::cout << "OS04_04_T1 PID = " << pid << ", TID = " << tid << " : "<< i << "\n";
        Sleep(1000);
        if (i == 25) 
        {
            std::cout << "OS04_04_T1 Sleep\n";
            Sleep(10*1000);
            std::cout << "OS04_04_T1 Wakeup\n";
        }
    }
    return 0;
}

DWORD WINAPI OS04_04_T2() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 1; i <= 125; i++) 
    {
        std::cout << "OS04_04_T2 PID = " << pid << ", TID = " << tid << " : "<< i << "\n";
        Sleep(1000);
        if (i == 80) 
        {
            std::cout << "OS04_04_T2 Sleep\n";
            Sleep(15*1000);
            std::cout << "OS04_04_T2 Wakeup\n";
        }
    }
    return 0;
}

int main() {
    DWORD pid = GetCurrentProcessId();
    DWORD ChildId1, ChildId2 = NULL;
    HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_04_T1, NULL, 0, &ChildId1);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_04_T2, NULL, 0, &ChildId2);

    for (int i = 1; i <= 100; i++) {
        std::cout << "main PID = " << pid << " : "<< i << "\n";
        Sleep(1000);

        if (i == 30) 
        {
            std::cout << "main Sleep\n";
            Sleep(10*1000);
            std::cout << "main Wakeup\n";
        }
    }
    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);
    CloseHandle(hChild1);
    CloseHandle(hChild2);
    return 0;
}