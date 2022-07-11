#include <iostream>
#include "../OS_HTAPI/HashTableAPI.h"
#include "../OS_HTCOM/HT.h"
#include <conio.h>
#include <string>
using namespace HT;
using namespace std;

#pragma comment(lib,"../Release/OS_HTAPI.lib")


int main(int argc, char** argv)
{
	try
	{
		HTHANDLE* HT = NULL;
		char* fileName = (char*)"D:\\create.txt";

		if (HTAPI::OpenApi())
		{
			if ((HT = HTAPI::Open(fileName)) == NULL) throw "error while creating a ht";
			
			printf("HT-Storage Created filename=%s, snapshotinterval=%d, capacity=%d, maxkeylength=%d, maxdatalength=%d\n", fileName, HT->SecSnapshotInterval, HT->Capacity, HT->MaxKeyLength, HT->MaxPayloadLength);
			
			
			char c = _getch();
			//Snap(HT);
			HTAPI::Close(HT);
			
			if (HTAPI::CloseApi() == false) printf("error with close api\n");
		}
		else 
		{
			printf("error with open api\n");
		}

	}
	catch (const char* message)
	{
		cout << endl << "Catch: " << message << endl;
	}
	return 0;
}