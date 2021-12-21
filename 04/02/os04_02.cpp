#include <Windows.h>
#include <iostream>

DWORD WINAPI OS04_02_T1() 
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 50; i++) 
    {
        std::cout << "OS04_02_T1 PID = " << pid << ", TID = " << tid << " : "<< i << "\n";
   	Sleep(1000);
    }
    return 0;
}

DWORD WINAPI OS04_02_T2() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 125; i++) 
    {
        std::cout << "OS04_02_T2 PID = " << pid << ", TID = " << tid << " : "<< i << "\n";
        Sleep(1000);
    }
    return 0;
}

int main() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    DWORD ChildId1, ChildId2 = NULL;
    HANDLE hChild1 = CreateThread(NULL,                         
        0,                                                      
        (LPTHREAD_START_ROUTINE)OS04_02_T1,                    
        NULL,                                                                                                                                                               //pointer to a var will be passed to the thread
        0,                                                      
        &ChildId1);                                             
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_02_T2, NULL, 0, &ChildId2);

    for (int i = 0; i < 100; i++) {
        std::cout << "main PID = " << pid << ", TID = " << tid << " : "<< i << "\n";
        Sleep(1000);
    }
    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);
    CloseHandle(hChild1);
    CloseHandle(hChild2);
    return 0;
}