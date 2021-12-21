#include <Windows.h>
#include <iostream>
#include <ctime>


volatile int Break = 0;

DWORD WINAPI Cycle() {;
	for (int i = 2; ; i++)
    {
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0) break;
            else if (i == j + 1)  printf("i = %d.\n", i);
            if (Break == 1) return 0;
        }
    }
	return 0;
}


int main()
{
    HANDLE htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, (LPCSTR)"OS08_04_2");
    DWORD AId = NULL;
    HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Cycle, NULL, 0, &AId);
    if (WaitForSingleObject(htimer, INFINITE) != WAIT_OBJECT_0)
            printf("WaitForSingleObject failed (%d)\n", GetLastError());
        else printf("Timer 2 was signaled.\n");
    Break = 1;
    CloseHandle(hA);
    CloseHandle(htimer);
    system("pause");
    return 0;
}

