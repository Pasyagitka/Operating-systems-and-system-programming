#define UNICODE 1
#define _UNICODE 1

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "string.h"

#define _SECOND 10000000

volatile long long *i = 0;


DWORD WINAPI Cycle() {
   DWORD time = GetTickCount();
	while (true) {
		i++;
      if(GetTickCount() - time >= 15000)  { break; }
      //Sleep(10);
	}
	return 0;
}

VOID CALLBACK TimerAPCProc(
   LPVOID lpArg,               // Data value
   DWORD dwTimerLowValue,      // Timer low value
   DWORD dwTimerHighValue )    // Timer high value

{
   UNREFERENCED_PARAMETER(dwTimerLowValue);
   UNREFERENCED_PARAMETER(dwTimerHighValue);
   printf( "i = : %d\n",  i);
}

int main( void ) 
{
   HANDLE          hTimer;
   __int64         qwDueTime;
   LARGE_INTEGER   liDueTime;
   DWORD Code;


   DWORD AId = NULL;
   HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Cycle, NULL, 0, &AId);

   hTimer = CreateWaitableTimer(NULL, FALSE, TEXT("MyTimer"));        
   // Default security attributes, Create auto-reset timer, Name of waitable timer
 
   if (hTimer != NULL)  {
         qwDueTime = -3 * _SECOND;
         liDueTime.LowPart  = (DWORD) ( qwDueTime & 0xFFFFFFFF );
         liDueTime.HighPart = (LONG)  ( qwDueTime >> 32 );

         if (SetWaitableTimer(hTimer, &liDueTime, 3000, TimerAPCProc, NULL, FALSE)) 
			   while (true) { 
               SleepEx( INFINITE, TRUE ); 
               GetExitCodeThread(hA, &Code);
               if (Code != STILL_ACTIVE) break;
            } // Put thread in an alertable state	
   }
   WaitForSingleObject(hA, INFINITE);
   CloseHandle(hA);
   CancelWaitableTimer(hTimer);
   CloseHandle(hTimer);
   return 0;
}