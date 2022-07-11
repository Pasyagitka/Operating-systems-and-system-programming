#include <iostream>
#include <conio.h>
#include "../OS11_HTAPI/HT.h"
#pragma comment(lib,"D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\02\\Debug\\OS11_HTAPI.dll")



using namespace std;
using namespace HT;

void PrintLastError(HTHANDLE* HT) {
	cout << "Last error: " << (GetLastErrorHT(HT)) << endl;
}


int main(int argc, char** argv)
{
	try
	{
		HTHANDLE* HT = NULL;
		char* fileName = (char*)"D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\02\\Debug\\create.txt";

		//fileName = argv[1];

		if ((HT = Open(fileName)) == NULL) throw "error while creating a ht";

		printf("HT-Storage Created filename=%s, snapshotinterval=%d, capacity=%d, maxkeylength=%d, maxdatalength=%d\n", fileName, HT->SecSnapshotInterval, HT->Capacity, HT->MaxKeyLength, HT->MaxPayloadLength);
		
		char c = _getch();
		//Snap(HT);
		Close(HT);
	}
	catch (const char* message)
	{
		cout << endl << "Catch: " << message << endl;
	}
	return 0;
}
