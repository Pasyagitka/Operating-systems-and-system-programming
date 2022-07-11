#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "../OS11_HTAPI/HT.h"
#include "../OS11_HTAPI/General.h"
#include <conio.h>
#pragma comment(lib,"D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\02\\Debug\\OS11_HTAPI.dll")
using namespace std;
using namespace HT;

#define KEYCOUNT 50
#define SIZE 3

static const char alphanum[] =
"abcdefghijklm";



int main(int argc, char** argv)
{
	try
	{
		HINSTANCE hDLL = NULL;
		hDLL = ::LoadLibraryA("D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\02\\Debug\\OS11_HTAPI.dll");
		if (hDLL == NULL) {
			throw "error while loading a DLL";
		}
		HTHANDLE* (*OpenSharedFunc)(char*) = (HTHANDLE * (*)(char*))GetProcAddress(hDLL, "OpenShared");
		HTHANDLE* (*UpdateFunc)(HTHANDLE*, Element*, void*, int) = (HTHANDLE * (*)(HTHANDLE*, Element*, void*, int))GetProcAddress(hDLL, "Update");
		HTHANDLE* (*PrintFunc)(const Element*) = (HTHANDLE * (*)(const Element*))GetProcAddress(hDLL, "print");
		Element* (*GetFunc)(HTHANDLE*, Element*) = (Element * (*)(HTHANDLE*, Element*))GetProcAddress(hDLL, "Get");
		char* (*GetLastErrorHTFunc)(HTHANDLE*) = (char * (*)(HTHANDLE*))GetProcAddress(hDLL, "GetLastErrorHT");
		Element* (*GetElementFunc)(const void*, int, const void*, int) = (Element * (*)(const void*, int, const void*, int))GetProcAddress(hDLL, "getElement");


		std::string tmp_s;
		HTHANDLE* HT = NULL;
		char* fileName = (char*)"D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\02\\Debug\\create.txt";


		fileName = argv[1];

		if ((HT = OpenSharedFunc(fileName)) == NULL) throw "error while opening a ht";

		srand(time(NULL));
		for (int i = 0; ; i++)
		{
			Sleep(1000);
			tmp_s.clear();
			tmp_s.reserve(SIZE);
			for (int i = 0; i < SIZE; ++i) tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
			const char* chr = tmp_s.c_str();


			Element* elInsert1 = GetElementFunc(chr, 4, "0", 4);

			char buff[4];
			_itoa(atoi((const char*)elInsert1->payload) + 1, buff, 10);

			if (!UpdateFunc(HT, elInsert1, buff, elInsert1->payloadlength)) {
				cout << "Last error: " << (GetLastErrorHTFunc(HT)) << endl;
				PrintFunc(elInsert1);
			}
			else {
				cout << "updated" << endl;
				PrintFunc(GetFunc(HT, elInsert1));
			}
		}

		_getch();
	}
	catch (const char* message)
	{
		cout << endl << "Catch: " << message << endl;
	}
	return 0;
}

