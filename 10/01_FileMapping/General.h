#pragma once
#include "HT.h"
#include <string>


namespace HT
{
	int SearchIndex(HTHANDLE* hthandle, Element* element);


	//int Hash(const std::string& key, int table_size);
	int Hash(const Element* element, int size);
	int NextHash(int hash, int size, int p);

	BOOL EqualElementKeys(Element* el1, Element* el2);

	DWORD WINAPI SnapTimer(HTHANDLE* hthandle);

	char* GetName(const char* pathToHT);


	Element* GetByIndex(HTHANDLE* ht, int n);

	BOOL DEL(Element* ptr);

	void SetLastError(HTHANDLE* ht, const char* message);
}
