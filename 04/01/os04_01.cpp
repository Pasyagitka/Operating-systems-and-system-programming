#include <Windows.h>
#include <iostream>

void main()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	for (int i = 0; i < 1000; i++)
	{
		std::cout << "PID = " << pid << ", TID = " << tid << std::endl;
		Sleep(1000);
	}
}