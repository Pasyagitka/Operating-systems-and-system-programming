#include <iostream>
#include "HT.h"

using namespace std;
using namespace HT;


#define FILENAME "D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\01\\file1.txt"
#define WRONG_FILENAME "D:\\6 semester\\Laboratory\\Operating-systems-and-system-programming\\01\\file111.txt"


void PrintLastError(HTHANDLE* HT) {
	cout << "Last error: " << (GetLastError(HT)) << endl;
}


int main()
{
	try
	{
		HTHANDLE* HT = NULL;
		Element* element;

		if ((HT = Create(10, 2, 12, 12, FILENAME)) == NULL) throw "error while creating a ht";
		//if ((HT = Create(10, 2, 12, 12, FILENAME)) == NULL) throw "error while creating a ht";


		Element* elInsert1 = new Element("m", 2, "ffffff", 7);
		Element* elInsert2 = new Element("me", 3, "wfeewf", 7);
		Element* elInsert3 = new Element("meo", 4, "wefwef", 7);
		Element* elInsert4 = new Element("neow", 5, "regkiehgri", 11);
		Element* elInsert5 = new Element("key", 3, "ebkenjgure", 11);
		Element* elInsert6 = new Element("uhvh", 4, "wefwifeefwufj", 14);
		Element* elInsert7 = new Element("uhvh", 4, "wefwifeefwufj", 14); //> max payload
		Element* elInsert8 = new Element("vosem", 8, "fe", 3);



		cout << endl << "Trying to insert into HT..." << endl;

		if (!Insert(HT, elInsert1))			PrintLastError(HT);
		else cout  << "Inseted successfully" << endl << endl;

		if (!Insert(HT, elInsert2))			PrintLastError(HT);
		else cout << "2 Inseted successfully" << endl << endl;

		if (!Insert(HT, elInsert3))			PrintLastError(HT);
		else cout << "3 Inseted successfully" << endl << endl;

		if (!Insert(HT, elInsert4)) 		PrintLastError(HT);		
		else cout << "4 Inseted successfully" << endl << endl;

		cout << "4 An attempt to insert duplicate key:";
		if (!Insert(HT, elInsert4)) 		PrintLastError(HT);	//duplicate insert
		else cout << " 4 Inseted successfully" << endl << endl;

		if (!Insert(HT, elInsert5)) 		PrintLastError(HT);
		else cout << "5 Inseted successfully" << endl << endl;

		if (!Insert(HT, elInsert6)) 		PrintLastError(HT);
		else cout << "6 Inseted successfully" << endl << endl;

		if (!Insert(HT, elInsert7)) 		PrintLastError(HT);
		else cout << "7 Inseted successfully" << endl << endl;

		if (!Insert(HT, elInsert8)) 		PrintLastError(HT);
		else cout << "8 Inseted successfully" << endl << endl;


		cout << "Inserting completed!" << endl << endl;


		if (Close(HT))			cout << "Storage closed\n";
		HT = NULL;

		if (Close(HT))			cout << "Storage closed\n";	//close slosed
		HT = NULL;

		/*if (!(element = Get(HT, elInsert4)))			PrintLastError(HT);
		else print(element);*/

		Sleep(5000);
		if ((HT = Open(WRONG_FILENAME)) == NULL) cout << endl << "wrog filename" << endl;	//open wrong ht
		if ((HT = Open(FILENAME)) == NULL) throw "error while opening a ht";				//open existing ht
		cout << "Storage opened\n";


		if (!(element = Get(HT, elInsert1))) 			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert2)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert3)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert4)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert5)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert6)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert7)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert8)))			PrintLastError(HT);
		else print(element);


		cout << endl <<  "Trying to update HT..." << endl;
		if (!Update(HT, elInsert1, elInsert5->payload, elInsert5->payloadlength)) 			PrintLastError(HT);
		if (!Update(HT, elInsert5, elInsert3->payload, elInsert3->payloadlength)) 			PrintLastError(HT);
		if (!Update(HT, elInsert1, elInsert4->payload, elInsert4->payloadlength)) 			PrintLastError(HT);
		cout << "Updating completed!" << endl << endl;


		if (Snap(HT)) cout << endl  << endl << "Manual snap!" << endl << endl;		//manual snap
		else PrintLastError(HT);


		if (!(element = Get(HT, elInsert1))) 			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert2)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert3)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert4)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert5)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert6)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert7)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert8)))			PrintLastError(HT);
		else print(element);
		


		Sleep(5000);

		cout << endl << "Trying to delete from HT..." << endl;
		if (!Delete(HT, elInsert1)) 			PrintLastError(HT);
		if (!Delete(HT, elInsert2)) 			PrintLastError(HT);
		if (!Delete(HT, elInsert3)) 			PrintLastError(HT);
		if (!Delete(HT, elInsert4)) 			PrintLastError(HT);
		if (!Delete(HT, elInsert6)) 			PrintLastError(HT);			//delete wrong
		cout << "Deleting completed!" << endl << endl;


		if (!(element = Get(HT, elInsert1))) 			PrintLastError(HT);	//get deleted elements
		else print(element);

		if (!(element = Get(HT, elInsert2)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert3)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert4)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert5)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert6)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert7)))			PrintLastError(HT);
		else print(element);

		if (!(element = Get(HT, elInsert8)))			PrintLastError(HT);
		else print(element);


		if (Close(HT))	 cout << "Storage closed\n";
		Sleep(5000);
	}
	catch (const char* message) 
	{
		cout << endl << "Catch: " << message << endl;
	}
	return 0;
}
