#include <Windows.h>
#include <iostream>

DWORD WINAPI OS04_03_T1() 
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 50; i++) 
    {
        Sleep(1000);
        std::cout << "OS04_03_T1 PID = " << pid << ", TID = " << tid << " : "<< i << "\n";
    }
    return 0;
}

DWORD WINAPI OS04_03_T2() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 125; i++) 
    {
        Sleep(1000);
        std::cout << "OS04_03_T2 PID = " << pid << ", TID = " << tid << " : "<< i << "\n";
    }
    return 0;
}

int main() {
    DWORD pid = GetCurrentProcessId();
    DWORD ChildId1, ChildId2 = NULL;
    HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_03_T1, NULL, 0, &ChildId1);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_03_T2, NULL, 0, &ChildId2);

    for (int i = 1; i <= 100; i++) {
        if (i == 20) 
        {
            SuspendThread(hChild1);
            std::cout << "\n-----------SuspendThread Child1-------------\n";
        }
        if (i == 40) 
        {
            SuspendThread(hChild2);
            std::cout << "\n-----------SuspendThread Child2-------------\n";
        }
        if (i == 60) 
        {
            ResumeThread(hChild1);
            std::cout << "\n-----------ResumeThread Child1-------------\n";
        }
        std::cout << "main PID = " << pid << " : "<< i << "\n";
        Sleep(1000);
    }
    ResumeThread(hChild2);
    std::cout << "\n-----------ResumeThread Child2-------------\n";
    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);
    CloseHandle(hChild1);
    CloseHandle(hChild2);
    return 0;
}