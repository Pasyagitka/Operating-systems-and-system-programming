#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

void printProcessPriority(HANDLE h)	{
	DWORD priority = GetPriorityClass(h);
	switch(priority) {
		case IDLE_PRIORITY_CLASS: 				cout << "Priority = IDLE_PRIORITY_CLASS" << endl; 			break;
		case BELOW_NORMAL_PRIORITY_CLASS: 		cout << "Priority = BELOW_NORMAL_PRIORITY_CLASS" << endl; 	break;
		case NORMAL_PRIORITY_CLASS: 			cout << "Priority = NORMAL_PRIORITY_CLASS" << endl; 		break;
		case ABOVE_NORMAL_PRIORITY_CLASS: 		cout << "Priority = ABOVE_NORMAL_PRIORITY_CLASS" << endl; 	break;
		case HIGH_PRIORITY_CLASS: 				cout << "Priority = HIGH_PRIORITY_CLASS" << endl; 			break;
		case REALTIME_PRIORITY_CLASS: 			cout << "Priority = REALTIME_PRIORITY_CLASS" << endl; 		break;
		default: cout << "Priority = ?" << endl; break;
	}
}

void printThreadPriority(HANDLE h) {
	DWORD priority = GetThreadPriority(h);
	switch(priority) {
		case THREAD_PRIORITY_LOWEST: 			cout << "Priority = THREAD_PRIORITY_LOWEST" << endl; 		break;
		case THREAD_PRIORITY_BELOW_NORMAL: 		cout << "Priority = THREAD_PRIORITY_BELOW_NORMAL" << endl; 	break;
		case THREAD_PRIORITY_NORMAL: 			cout << "Priority = THREAD_PRIORITY_NORMAL" << endl; 		break;
		case THREAD_PRIORITY_ABOVE_NORMAL: 		cout << "Priority = THREAD_PRIORITY_ABOVE_NORMAL" << endl; 	break;
		case THREAD_PRIORITY_HIGHEST: 			cout << "Priority = THREAD_PRIORITY_HIGHEST" << endl; 		break;
		case THREAD_PRIORITY_IDLE: 				cout << "Priority = THREAD_PRIORITY_IDLE" << endl; 			break;
		case THREAD_PRIORITY_TIME_CRITICAL: 	cout << "Priority = THREAD_PRIORITY_TIME_CRITICAL" << endl; break;
		default: cout << "Priority = ?" << endl; break;
	}	
}

void printIdealProcessor(HANDLE h) {
	DWORD idealProcessor = -1;
	idealProcessor = SetThreadIdealProcessor(h, MAXIMUM_PROCESSORS);
	cout << "Thread ideal processor: " << dec << idealProcessor << endl;
}

DWORD WINAPI TA()
{
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();
	for (int i = 0; i < 1000000; i++) {
		if (i % 1000 == 0) {
		    cout << "--------------------------------------\ni = " << i << endl;
			cout << "PID: " << GetCurrentProcessId() << endl << "TID: " << GetCurrentThreadId() << endl;			
			printProcessPriority(hp);
			printThreadPriority(ht);
			printIdealProcessor(ht);
			Sleep(200);
		}	
	}
	return 0;
}


int main(int argc, char* argv[])
{
	try {
		if (argc == 5) {
			char buf[10];
			int p1 = atoi(argv[1]);
			int p2 = atoi(argv[2]);
			int p3 = atoi(argv[3]);
			int p4 = atoi(argv[4]);
			
			if (!SetProcessAffinityMask(GetCurrentProcess(), p1)) 		throw "SetProcessAffinityMask";
			SetPriorityClass(GetCurrentProcess(), p2);

			_itoa_s(p1, buf, 2);
			cout << "processAffinityMask: " << buf << endl;
			cout << "processPriorityClass: " << p2 << endl;
			cout << "threadPriorityClass1: " << p3 << endl;
			cout << "threadPriorityClass2: " << p4 << endl;

			DWORD ChildId1 = NULL, ChildId2 = NULL;
			HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId1);
			HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &ChildId2);
			SetThreadPriority(hChild1, p3);
			SetThreadPriority(hChild2, p4);
			ResumeThread(hChild1);
			ResumeThread(hChild2);
			WaitForSingleObject(hChild1, INFINITE);
			WaitForSingleObject(hChild2, INFINITE);
			CloseHandle(hChild1);
			CloseHandle(hChild2);
		}
		else {cout << "No arguments" << endl; }
	}
	catch (string err) {
		cout << "error" << endl;
	}
	system("pause");
}