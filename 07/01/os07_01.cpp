
#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

void EnterCriticalSectionAssem() { 
	_asm {
	CriticalSection:
		//cf 1
		lock bts o, 0;//lock устанавливает сигнал на линии LOCK системной шины и запрещает доступ к шине другим процессорам на время выполнения данной команды.
		jc CriticalSection
	}
}
void LeaveCriticalSectionAssem() {
	//-> CF, cf 0.
	_asm lock btr o, 0
}

DWORD WINAPI F(int s) {
	int start = clock();
	EnterCriticalSectionAssem();
	for (int i = 0; i < 5; i++) {
		cout << s << " " << i << ", time: " << clock() - start << endl;
	}
	LeaveCriticalSectionAssem();
	return 0;
}


int o = 0;

int main() {
	DWORD AId = NULL, BId = NULL;
	HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)F, (LPVOID)1, 0, &AId);
	HANDLE hB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)F, (LPVOID)2, 0, &BId);

	WaitForSingleObject(hA, INFINITY);	
    WaitForSingleObject(hB, INFINITY);
	CloseHandle(hA); 
    CloseHandle(hB);
	system("pause");
	return 0;
}
