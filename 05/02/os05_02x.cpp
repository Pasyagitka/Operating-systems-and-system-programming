#include <Windows.h>
#include <iostream>
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

int main(){	
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();
	
	for (int i = 0; i < 1000000; i++) {
		if (i % 1000 == 0) {
		    cout << "--------------------------------------\ni = " << i << endl;
			cout << "PID: " << GetCurrentProcessId() << endl << "TID: " << GetCurrentThreadId()  << endl;			
			printProcessPriority(hp);
			printThreadPriority(ht);
			printIdealProcessor(ht);
			Sleep(200);
		}	
	}
	system("pause");
}