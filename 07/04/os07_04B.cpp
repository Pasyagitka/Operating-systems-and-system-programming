#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int start;

int main() {
    start = clock();

    DWORD pid = GetCurrentProcessId();
    HANDLE hm = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, (LPCSTR)"Semaphore");

    hm == NULL ? cout << "OS07_04B: Open Error Semaphore\n" : cout << "OS07_04B: Open Semaphore\n";

    LONG prevcount = 0;
    for (int i = 1; i <= 90; i++)  {
        if (i == 30) {
            cout << i << "------------WaitForSingleObject OS07_04B------------" << endl;
            WaitForSingleObject(hm, INFINITE);
        }
        if (i == 60) {
            cout << i << "------------ReleaseSemaphore OS07_04B------------" << endl;
            ReleaseSemaphore(hm, 1, &prevcount);
        }
        cout << i << " OS07_04B pid = " << pid << ", time: " << clock() - start << endl;
        Sleep(100);
    }
    CloseHandle(hm);
    system("pause");
}