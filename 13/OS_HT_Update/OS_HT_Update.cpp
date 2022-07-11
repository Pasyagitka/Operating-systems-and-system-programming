#define _CRT_SECURE_NO_WARNINGS

//#include <iostream>
//#include "../OS_HTAPI/HashTableAPI.h"
//#include "../OS_HTAPI/HashTable.h"
//#include <string>
//
//#pragma comment(lib,"../Release/OS_HTAPI.lib")
//using namespace std;
//
//string key = "my_key";
//string value = "my_value";
//HT::HTHANDLE* ht = NULL;
//
//
//
//
//void Do(LPCSTR FileName) 
//{
//	//path of mapping file
//	char cwd[MAX_PATH];
//	GetModuleFileNameA(NULL, cwd, MAX_PATH);
//	string path(cwd);
//	int pos = path.find_last_of("\\") + 1;
//	string filePath = path.substr(0, pos) + "HashTables\\" + FileName;
//	char* filePathCost = (char*)filePath.c_str();
//	DWORD er;
//
//	HT::HTHANDLE* ht = HTAPI::Open(filePathCost);
//	if (ht != NULL) 
//	{
//		printf("\nHT-Storage Created filename=%s, snapshotinterval=%d, capacity = %d, maxkeylength = %d, maxdatalength = %d",
//			filePathCost, ht->SecSnapshotInterval, ht->Capacity, ht->MaxKeyLength, ht->MaxPayloadLength);
//	}
//	else 
//	{
//		printf("\n error: %d", GetLastError());
//		return;
//	}
//	srand(time(NULL));
//	HT::Element* element;
//	int random;
//	int value = 0;
//	while (true) 
//	{
//		random = rand() % 50;
//		element = new HT::Element((void*)&random, 4, &value, 4);
//		element = HTAPI::Get(ht, element);
//		if (element != NULL) 
//		{
//			printf("\nSuccessful getting element with key: %d. Value: %d", *(int*)element->key, *(int*)element->payload);
//			value = *(int*)element->payload + 1;
//			if (HTAPI::Update(ht, element, &value, 4)) 
//			{
//				printf("\nSuccessful updating element with key: %d. OldValue: %d", *(int*)element->key, *(int*)element->payload);
//			}
//			else 
//			{
//				printf("\nFail with updating key: %d. Message: %s", random, HTAPI::GetLastErrorHT(ht));
//			}
//		}
//		else 
//		{
//			printf("\nFail with getting key: %d. Message: %s", random, HTAPI::GetLastErrorHT(ht));
//		}
//		Sleep(1000);
//	}
//
//
//	HTAPI::Close(ht);
//}
//
//int main(int argc, char* argv[])
//{
//
//	if (HTAPI::OpenApi()) 
//	{
//
//		if (argc != 2) 
//		{
//			printf("\nProgram need 1 parameter! argc: %d.\nDefault parameters are used", argc);
//			argv[1] = (char*)"showcase.txt";
//		}
//		Do(argv[1]);
//
//
//		if (HTAPI::CloseApi() == false)
//			printf("error with close api\n");
//	}
//	else 
//	{
//		printf("error with open api\n");
//	}
//	return 0;
//}


#include <iostream>
#include "../OS_HTAPI/HashTableAPI.h"
#include "../OS_HTCOM/HT.h"
#include <string>

#pragma comment(lib,"../Release/OS_HTAPI.lib")
using namespace std;

string key = "my_key";
string value = "my_value";
HT::HTHANDLE* ht = NULL;


//void Do(LPCSTR FileName) 
//{
//	//path of mapping file
//	char cwd[MAX_PATH];
//	GetModuleFileNameA(NULL, cwd, MAX_PATH);
//	string path(cwd);
//	int pos = path.find_last_of("\\") + 1;
//	string filePath = path.substr(0, pos) + "HashTables\\" + FileName;
//	char* filePathCost = (char*)filePath.c_str();
//	DWORD er;
//
//	HT::HTHANDLE* ht = HTAPI::Open(filePathCost);
//	if (ht != NULL) 
//	{
//		printf("\nHT-Storage Created filename=%s, snapshotinterval=%d, capacity = %d, maxkeylength = %d, maxdatalength = %d",
//			filePathCost, ht->SecSnapshotInterval, ht->Capacity, ht->MaxKeyLength, ht->MaxPayloadLength);
//	}
//	else 
//	{
//		printf("\n error: %d", GetLastError());
//		return;
//	}
//	srand(time(NULL));
//	HT::Element* element;
//	int random;
//	int value = 0;
//
//	while (true) 
//	{
//		random = rand() % 50;
//		element = new HT::Element((void*)&random, 4, (void*)&value, 4);
//		if (HTAPI::Insert(ht, element)) 
//		{
//			printf("\nSuccessful inserting key: %d", random);
//		}
//		else 
//		{
//			printf("\nFail with inserting key: %d. Message: %s", random, HTAPI::GetLastErrorHT(ht));
//		}
//		Sleep(1000);
//	}
//
//	HTAPI::Close(ht);
//}
//
//int main(int argc, char* argv[])
//{
//	if (HTAPI::OpenApi()) 
//	{
//		if (argc != 2) 
//		{
//			printf("\nProgram need 1 parameter! argc: %d.\nDefault parameters are used", argc);
//			argv[1] = (char*)"showcase.txt";
//		}
//		Do(argv[1]);
//
//
//		if (HTAPI::CloseApi() == false)
//			printf("error with close api\n");
//	}
//	else 
//	{
//		printf("error with open api\n");
//	}
//	return 0;
//}


#define KEYCOUNT 50
#define SIZE 3

using namespace HT;

static const char alphanum[] =
"abcdefghijklm";


int main(int argc, char** argv)
{
	try
	{
		if (HTAPI::OpenApi())
		{
			std::string tmp_s;
			HTHANDLE* HT = NULL;
			char* fileName = (char*)"D:\\create.txt";

			//fileName = argv[1];

			if ((HT = HTAPI::OpenShared(fileName)) == NULL) throw "error while opening a ht";

			srand(time(NULL));
			for (int i = 0; ; i++)
			{
				Sleep(1000);
				tmp_s.clear();
				tmp_s.reserve(SIZE);
				for (int i = 0; i < SIZE; ++i) tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
				const char* chr = tmp_s.c_str();


				Element* elInsert1 = HTAPI::GetElement(chr, 4, "0", 4);

				char buff[4];
				_itoa(atoi((const char*)elInsert1->payload) + 1, buff, 10);

				if (!HTAPI::Update(HT, elInsert1, buff, elInsert1->payloadlength)) {
					cout << "Last error: " << (HTAPI::GetLastErrorHT(HT)) << endl;
					//Printc(elInsert1);
				}
				else {
					cout << "updated" << endl;
					//Print(Get(HT, elInsert1));
				}
			}

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

