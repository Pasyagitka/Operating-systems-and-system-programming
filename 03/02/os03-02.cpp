#include <iostream>
#include <process.h>
#include "Windows.h"

void main()
{
	LPCSTR an1 = "D:\\5 семестр\\Laboratory\\Operating-systems-and-system-programming\\03\\02\\os03-02_1.exe";
	LPCSTR an2 = "D:\\5 семестр\\Laboratory\\Operating-systems-and-system-programming\\03\\02\\os03-02_2.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
	
	if (
		CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1)
	)
		std::cout << "-- Process os03-02_1 created\n";
	else std::cout << "-- Process os03-02_1 not created\n\n";

	if (
		CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2)
	)
		std::cout << "-- Process os03-02_2 created\n";
	else std::cout << "-- Process os03-02_2 not created\n\n";


  	for (int i=0; i<100;i++)
	{
 		std::cout << getpid() << std::endl;
   		Sleep(1000);
  	}
	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);
}