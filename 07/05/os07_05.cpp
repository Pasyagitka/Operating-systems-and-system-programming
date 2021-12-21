#include <Windows.h>
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    int start = clock();
    DWORD pid = GetCurrentProcessId();
    HANDLE he = CreateEvent(NULL, TRUE, FALSE, (LPCSTR)"Event");

    LPCSTR an1 = (LPCSTR)"OS07_05A.exe";
    LPCSTR an2 = (LPCSTR)"OS07_05B.exe";

    STARTUPINFO si1; 
    STARTUPINFO si2;
    PROCESS_INFORMATION pi1; 
    PROCESS_INFORMATION pi2;
    ZeroMemory(&si1, sizeof(STARTUPINFO)); 
    ZeroMemory(&si2, sizeof(STARTUPINFO));
    si1.cb = sizeof(STARTUPINFO); 
    si2.cb = sizeof(STARTUPINFO);

    if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1)) 
        cout << "--Process OS07_05B created\n";
    else cout << "--Process OS07_05B not created\n";

    if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
        cout << "--Process OS07_05B created\n";
    else  cout << "--Process OS07_05B not created\n";

    LONG prevcount = 0;
    for (int i = 1; i <= 90; i++) {
        if (i == 15) {
            PulseEvent(he);
        }
        cout << i << " OS07_05 pid = " << pid << ", time: " << clock() - start << endl;
        Sleep(100);
    }
    WaitForSingleObject(pi1.hProcess, INFINITE);  
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(he);
    CloseHandle(pi1.hProcess);  
    CloseHandle(pi2.hProcess);

    system("pause");
    return 0;
}