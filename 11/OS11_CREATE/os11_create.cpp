#include <iostream>
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
		int capacity = 200, secSnapshotInterval = 3, maxKeyLength = 4, maxPayloadLength = 4;
		char* fileName = (char*)"D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\02\\Debug\\create.txt";
		//char* fileName = (char*)"D:\\create.txt";

		//if (argc != 6) throw "check cmd parameters";
		
			
		/*capacity = atoi(argv[1]);
		secSnapshotInterval = atoi(argv[2]);
		maxKeyLength = atoi(argv[3]);
		maxPayloadLength = atoi(argv[4]);
		fileName = argv[5];*/
		

		if ((HT = Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, fileName)) == NULL) throw "error while creating a ht";

		printf("HT-Storage Created filename=%s, snapshotinterval=%d, capacity=%d, maxkeylength=%d, maxdatalength=%d\n", fileName, HT->SecSnapshotInterval, capacity, maxKeyLength, maxPayloadLength);
	}
	catch (const char* message)
	{
		cout << endl << "Catch: " << message << endl;
	}
	return 0;
}
