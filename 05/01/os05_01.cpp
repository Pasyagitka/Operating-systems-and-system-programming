#include <Windows.h>
#include <iostream>
#include <bitset>
using namespace std;

void printProcessPriority(HANDLE h) {
	DWORD priority = GetPriorityClass(h);
	cout << "\nCurrent PID = " << GetCurrentProcessId() << endl;
	switch(priority) {
		case IDLE_PRIORITY_CLASS: 			cout << "Priority = IDLE_PRIORITY_CLASS" << endl; 			break;
		case BELOW_NORMAL_PRIORITY_CLASS: 	cout << "Priority = BELOW_NORMAL_PRIORITY_CLASS" << endl; 	break;
		case NORMAL_PRIORITY_CLASS:		 	cout << "Priority = NORMAL_PRIORITY_CLASS" << endl; 		break;
		case ABOVE_NORMAL_PRIORITY_CLASS: 	cout << "Priority = ABOVE_NORMAL_PRIORITY_CLASS" << endl; 	break;
		case HIGH_PRIORITY_CLASS: 			cout << "Priority = HIGH_PRIORITY_CLASS" << endl; 			break;
		case REALTIME_PRIORITY_CLASS: 		cout << "Priority = REALTIME_PRIORITY_CLASS" << endl; 		break;
		default: cout << "Priority = ?" << endl; 														break;
	}
}

void printThreadPriority(HANDLE h) {
	DWORD priority = GetThreadPriority(h);
	cout << "\nCurrent thread ID = " << GetCurrentThreadId() << endl;
	switch(priority)
	{
		case THREAD_PRIORITY_LOWEST: 		cout << "Priority = THERAD_PRIORITY_LOWEST" << endl; 		break;
		case THREAD_PRIORITY_BELOW_NORMAL: 	cout << "Priority = THERAD_PRIORITY_BELOW_NORMAL" << endl; 	break;
		case THREAD_PRIORITY_NORMAL: 		cout << "Priority = THERAD_PRIORITY_NORMAL" << endl; 		break;
		case THREAD_PRIORITY_ABOVE_NORMAL: 	cout << "Priority = THERAD_PRIORITY_ABOVE_NORMAL" << endl; 	break;
		case THREAD_PRIORITY_HIGHEST: 		cout << "Priority = THERAD_PRIORITY_HIGHEST" << endl; 		break;
		case THREAD_PRIORITY_IDLE: 			cout << "Priority = THERAD_PRIORITY_IDLE" << endl; 			break;
		case THREAD_PRIORITY_TIME_CRITICAL: cout << "Priority = THREAD_PRIORITY_TIME_CRITICAL" << endl; break;
		default: cout << "Priority = ?" << endl; 														break;
	}	
}

void printAffinityMask(HANDLE h) {
	DWORD processAffinityMask = NULL, threadAffinityMask = NULL;

	if (!GetProcessAffinityMask(h, &processAffinityMask, &threadAffinityMask))  throw "GetProcessAffinityMask";
	
	bitset<8> mask(processAffinityMask);
	cout << "\nProcess affinity mask: " << mask << endl;
	
	cout << "Processors count: " << mask.count() << endl << endl;
}

void printIdealProcessor(HANDLE h) {
	DWORD idealProcessor = -1;
	idealProcessor = SetThreadIdealProcessor(h, MAXIMUM_PROCESSORS);
	cout << "Thread ideal processor: " << dec << idealProcessor << endl;
}

int main() {	
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();
	printProcessPriority(hp);
	printThreadPriority(ht);
	printAffinityMask(hp);
	printIdealProcessor(ht);
	return 0;
}