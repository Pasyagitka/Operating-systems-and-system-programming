#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int start;

int main() {
    start = clock();

    DWORD pid = GetCurrentProcessId();
    HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, (LPCSTR)"Mutex");

    hm == NULL ? cout << "OS07_03A: Open Error Mutex\n" : cout << "OS07_03A: Open Mutex\n";

    for (int i = 1; i <= 90; i++)  {
        if (i == 30) {
            cout << i << "------------WaitForSingleObject OS07_03A------------" << endl;
            WaitForSingleObject(hm, INFINITE);
        }
        if (i == 60) {
            cout << i << "------------ReleaseMutex OS07_03A------------" << endl;
            ReleaseMutex(hm);
        }
        cout << i << " OS07_03A pid = " << pid << ", time: " << clock() - start << endl;
        Sleep(100);
    }
    CloseHandle(hm);
    system("pause");
}