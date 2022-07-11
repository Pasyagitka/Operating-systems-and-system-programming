#include <iostream>
#include "../OS_HTAPI/HashTableAPI.h"
#include "../OS_HTCOM/HT.h"
#include <string>

#pragma comment(lib,"../Release/OS_HTAPI.lib")

using namespace std;
using namespace HT;

int main(int argc, char** argv)
{
	try
	{
		printf("create\n");
		HTHANDLE* HT = NULL;
		int capacity = 200, secSnapshotInterval = 3, maxKeyLength = 4, maxPayloadLength = 4;
		char* fileName = (char*)"D:\\create.txt";

		capacity = atoi(argv[1]);
		secSnapshotInterval = atoi(argv[2]);
		maxKeyLength = atoi(argv[3]);
		maxPayloadLength = atoi(argv[4]);
		fileName = argv[5];

		if (HTAPI::OpenApi())
		{
			HT::HTHANDLE* ht = HTAPI::Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, fileName);

			if (HTAPI::CloseApi() == false)			printf("error with close api\n");
		}
		else 
		{
			printf("error with open api\n");
		}

		printf("HT-Storage Created filename=%s, snapshotinterval=%d, capacity=%d, maxkeylength=%d, maxdatalength=%d\n", fileName, secSnapshotInterval, capacity, maxKeyLength, maxPayloadLength);
	}
	catch (const char* message)
	{
		cout << endl << "Catch: " << message << endl;
	}
	return 0;
}
