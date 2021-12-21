#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

DWORD WINAPI Cycle(char* threadName);

CRITICAL_SECTION cs;

int main() {
	DWORD AId = NULL, BId = NULL;

	InitializeCriticalSection(&cs);

	HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Cycle, (char*)"A", 0, &AId);
	HANDLE hB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Cycle, (char*)"B", 0, &BId);
	
	
	Cycle("Main");

	WaitForSingleObject(hA, INFINITE);	
	WaitForSingleObject(hB, INFINITE);

	

	DeleteCriticalSection(&cs);
	CloseHandle(hA); 
	CloseHandle(hB);
	return 0;
}

DWORD WINAPI Cycle(char* name) {
	for (int i = 1; i <= 90; i++) {
		if (i == 30) {
			//while(!TryEnterCriticalSection(&cs)) {}
			EnterCriticalSection(&cs);
		}
		if (i == 60) {
			LeaveCriticalSection(&cs);
		}
		printf("%s, %d\n", name, i);
		Sleep(100);
	}
	return 0;
}