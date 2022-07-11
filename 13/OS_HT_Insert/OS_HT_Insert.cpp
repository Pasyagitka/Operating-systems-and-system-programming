#include <iostream>
#include "../OS_HTAPI/HashTableAPI.h"
#include "../OS_HTCOM/HT.h"
#include <string>

#pragma comment(lib,"../Release/OS_HTAPI.lib")
using namespace std;


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
				if (!HTAPI::Insert(HT, elInsert1)) 	cout << "Last error: " << (HTAPI::GetLastErrorHT(HT)) << endl;
				else cout << "Inseted successfully" << endl << endl;
				//HTAPI(elInsert1);
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

