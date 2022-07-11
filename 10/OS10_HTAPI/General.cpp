#include "HT.h";
#include "General.h";
#include <string>
using namespace std;

namespace HT
{
	//https://studopedia.org/12-22525.html
	//Аддитивный метод, в котором ключом является символьная строка. 
	//В хеш-функции строка преобразуется в целое суммированием всех символов и 
	//возвращается остаток от деления на m (обычно размер таблицы m = 256).
	int Hash(const Element* element, int m)
	{
		char* dest = new char[element->keylength];
		strcpy_s(dest, element->keylength + 1, (char*)element->key);
		int s = 0;
		for (int i = 0; i < strlen(dest); ++i)
		{
			s += dest[i];
		}
		return s % m;
	}

	int NextHash(int hash, int size, int p)
	{
		return (hash + 10 * p + 3 * p * p) % size;
	}


	int SearchIndex(HTHANDLE* hthandle, Element* element)
	{
		int t = -1;
		bool b = false;
		if (hthandle->N != 0) {
			for (int i = 0, j = Hash(element, hthandle->Capacity);
				GetByIndex(hthandle, j) != NULL && i != hthandle->Capacity && !b; j = NextHash(j, hthandle->Capacity, ++i))
			{
				Element* elFromHT = GetByIndex(hthandle, j);
				if (!DEL(elFromHT))
				{
					if (memcmp(elFromHT->key, element->key, elFromHT->keylength) == 0)
					{
						t = j; b = true;
					}
				}
			}
		}
		return t;
	}

	Element* GetByIndex(HTHANDLE* ht, int n)
	{
		void* htPointer = ht + 1;

		int size = SINGLE_ELEMENT_SIZE(ht);
		char* elementPointer = (char*)htPointer + size * n;


		Element* element = new Element();
		element->key = elementPointer;

		elementPointer += ht->MaxKeyLength;
		element->keylength = *((int*)elementPointer);

		elementPointer += sizeof(element->keylength);
		element->payload = elementPointer;

		elementPointer += ht->MaxPayloadLength;
		element->payloadlength = *((int*)elementPointer);


		if (element->keylength == 0)
		{
			delete element;
			return NULL;
		}
		return element;
	}


	BOOL DEL(Element* element)
	{
		return (*(int*)element->key == -1);
	}


	void SetLastError(HTHANDLE* ht, const char* message)
	{
		if (ht == NULL)  throw  "SetLastError: handle null";
		strcpy_s(ht->LastErrorMessage, message);
	}


	char* GetName(const char* filename)
	{
		char mutex[MAX_PATH];
		for (int i = 0, j = 0; i < strlen(filename); i++)
		{
			if (filename[i] != '\\') mutex[j++] = filename[i];
		}
		return mutex;
	}
}