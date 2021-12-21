#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000;

using namespace std;

int main()
{
    long long it = -60 * SECOND;
    long long it2 = -120 * SECOND;
    HANDLE htimer = CreateWaitableTimer(NULL, TRUE, (LPCSTR)"OS08_04_1");
    if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, NULL, NULL, NULL, FALSE)) { 
        throw "Error SrtWaitableTimer"; 
    }
    HANDLE htimer2 = CreateWaitableTimer(NULL, TRUE, (LPCSTR)"OS08_04_2");
    if (!SetWaitableTimer(htimer2, (LARGE_INTEGER*)&it2, NULL, NULL, NULL, FALSE)) { 
        throw "Error SrtWaitableTimer"; 
    }
    

    LPCSTR an1 = (LPCSTR)"OS08_04_1.exe";
    LPCSTR an2 = (LPCSTR)"OS08_04_2.exe";
    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;
    ZeroMemory(&si1, sizeof(STARTUPINFO)); 
    ZeroMemory(&si2, sizeof(STARTUPINFO));
    si1.cb = sizeof(STARTUPINFO); 
    si2.cb = sizeof(STARTUPINFO);

    if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1)) {
        cout << "--Process OS08_04_X 1 created\n";
    }
    else {	cout << "--Process OS08_04_X 1 not created\n";}

    if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2)) {
        cout << "--Process OS08_04_X 2 created\n";
    }
    else {cout << "--Process OS08_04_X 2 not created\n";}

    if (WaitForSingleObject(htimer, INFINITE) != WAIT_OBJECT_0)
            printf("WaitForSingleObject failed (%d)\n", GetLastError());
        else printf("Timer was signaled.\n");
    if (WaitForSingleObject(htimer2, INFINITE) != WAIT_OBJECT_0)
            printf("WaitForSingleObject failed (%d)\n", GetLastError());
        else printf("Timer 2 was signaled.\n");

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CancelWaitableTimer(htimer);
    CancelWaitableTimer(htimer2);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
}