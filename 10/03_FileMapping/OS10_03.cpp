#include <iostream>
#include "HT.h"

using namespace std;
using namespace HT;

#define FILENAME1 "D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\01\\file31.txt"
#define FILENAME2 "D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\01\\file32.txt"


void PrintLastError(HTHANDLE* HT) {
	cout << "Last error: " << (GetLastError(HT)) << endl;
}


int main()
{
	try
	{
		Element* element;

		HTHANDLE* HT1 = Create(10, 1, 10, 15, FILENAME1);
		HTHANDLE* HT2 = Create(10, 1, 10, 15, FILENAME2);

		if (HT1 == NULL) 			throw "Invalid handle";


		Element* elInsert1 = new Element("m", 2, "ffffff", 7);
		Element* elInsert2 = new Element("me", 3, "wfeewf", 7);
		Element* elInsert3 = new Element("meo", 4, "wefwef", 7);
		Element* elInsert4 = new Element("neow", 5, "regkiehgri", 11);
		Element* elInsert5 = new Element("key", 3, "ebkenjgure", 11);

		cout << endl << "Trying to insert into HT1..." << endl;

		if (!Insert(HT1, elInsert1))			PrintLastError(HT1);
		else cout << "Inseted successfully" << endl << endl;

		if (!Insert(HT1, elInsert2))			PrintLastError(HT1);
		else cout << "2 Inseted successfully" << endl << endl;

		if (!Insert(HT1, elInsert3))			PrintLastError(HT1);
		else cout << "3 Inseted successfully" << endl << endl;

		if (!Insert(HT1, elInsert4)) 		PrintLastError(HT1);
		else cout << "4 Inseted successfully" << endl << endl;


		cout << endl << "Trying to insert into HT2..." << endl;

		if (!Insert(HT2, elInsert1))			PrintLastError(HT1);
		else cout << "Inseted successfully" << endl << endl;

		if (!Insert(HT2, elInsert2))			PrintLastError(HT1);
		else cout << "2 Inseted successfully" << endl << endl;

		if (!Insert(HT2, elInsert3))			PrintLastError(HT1);
		else cout << "3 Inseted successfully" << endl << endl;

		if (!Insert(HT2, elInsert5)) 		PrintLastError(HT1);
		else cout << "5 Inseted successfully" << endl << endl;


		cout << "HT1" << endl;
		if (!(element = Get(HT1, elInsert1))) 			PrintLastError(HT1);
		else print(element);

		if (!(element = Get(HT1, elInsert2)))			PrintLastError(HT1);
		else print(element);

		if (!(element = Get(HT1, elInsert3)))			PrintLastError(HT1);
		else print(element);

		if (!(element = Get(HT1, elInsert4)))			PrintLastError(HT1);
		else print(element);



		cout << "HT2" << endl;
		if (!(element = Get(HT2, elInsert1))) 			PrintLastError(HT2);
		else print(element);

		if (!(element = Get(HT2, elInsert2)))			PrintLastError(HT2);
		else print(element);

		if (!(element = Get(HT2, elInsert3)))			PrintLastError(HT2);
		else print(element);

		if (!(element = Get(HT2, elInsert5)))			PrintLastError(HT2);
		else print(element);


		

		cout << endl << "Trying to update HT1..." << endl;
		if (!Update(HT1, elInsert1, elInsert3->payload, elInsert5->payloadlength)) 			PrintLastError(HT1);
		cout << "Updating completed!" << endl << endl;


		if (Snap(HT1)) cout << "Snap H1" << endl;	else PrintLastError(HT1);


		Sleep(3000);

	
		
		cout << "Closing...\n";
		if (Close(HT1))			cout << "HT1 storage closed\n";
		Sleep(5000);
		if (Close(HT2))			cout << "HT2 storage closed\n"; else cout << "?";
	}
	catch (const char* mess) {
		cout << "Catch: " << mess << endl;
	}

	return 0;
}
