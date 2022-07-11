#include "General.h";
#include "HT.h";
#include <string>
using namespace std;


namespace HT {
	DWORD WINAPI SnapTimer(HTHANDLE* hthandle)
	{
		HANDLE          hTimer;
		LARGE_INTEGER   liDueTime{ 0, 0 };

		DWORD AId = NULL;
		hTimer = CreateWaitableTimerA(NULL, FALSE, GetName(hthandle->FileName));

		hthandle->SnapTimer = hTimer;

		if (hTimer != NULL)
		{
			if (SetWaitableTimer(hthandle->SnapTimer, &liDueTime, hthandle->SecSnapshotInterval * 1000, NULL, NULL, FALSE))
			{
				while (true)
				{
					WaitForSingleObject(hthandle->SnapTimer, INFINITE);
					Snap(hthandle);
				}
			}
		}
		return 0;
	}
}
