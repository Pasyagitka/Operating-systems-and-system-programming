#include "HT.h";
#include "General.h";
using namespace std;
#define HTAPI_EXPORTS


#define _SECOND 10000000

#define NAMEE "D6semesterLaboratoryOperatingsystemsandsystemprogramming02Debugcreatetxt" //todo name!

namespace HT
{

	HTHANDLE::HTHANDLE()
	{
		this->File = nullptr;
		this->FileMapping = nullptr;
		this->Addr = nullptr;
		this->Mutex = nullptr;
	}

	HTHANDLE::HTHANDLE(HANDLE hf, HANDLE hm, LPVOID lp, const char FileName[512])
	{
		this->File = hf;
		this->FileMapping = hm;
		this->Addr = lp;
		this->Mutex = CreateMutexA(NULL, FALSE, GetName(FileName));
	}

	HTHANDLE::HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
	{
		this->Capacity = Capacity;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
		this->N = 0;
		memcpy(this->FileName, FileName, sizeof(this->FileName));
	}

	HTHANDLE::HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512], HANDLE hf, HANDLE hm, LPVOID lp)
	{
		this->Capacity = Capacity;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
		this->N = 0;
		memcpy(this->FileName, FileName, sizeof(this->FileName));

		this->File = hf;
		this->FileMapping = hm;
		this->Addr = lp;
		this->lastsnaptime = time(NULL);
		this->Mutex = CreateMutexA(NULL, FALSE, GetName(FileName));
	}


	HTHANDLE* Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
	{
		try
		{
			HANDLE hf, hm;
			LPVOID lp;
			DWORD ThreadId = NULL;

			DWORD HTsize = sizeof(HTHANDLE) + Capacity * (MaxKeyLength + MaxPayloadLength + 2 * sizeof(int));

			if ((hf = CreateFileA(FileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)	throw "create file error";
			if (!(hm = CreateFileMappingA(hf, NULL, PAGE_READWRITE, 0, HTsize, NAMEE))) throw "create filemapping error";
			if (!(lp = MapViewOfFile(hm, FILE_MAP_ALL_ACCESS, 0, 0, 0))) throw "mapping file error";

			HTHANDLE* ht = new(lp) HTHANDLE(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, FileName, hf, hm, lp);

			if (!(ht->SnapThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SnapTimer, ht, 0, &ThreadId))) throw "cannot create snapshot thread";

			return ht;
		}
		catch (const char* message)
		{
			return NULL;
		}
	}

	HTHANDLE* OpenShared(const char FileName[512])
	{
		try
		{
			HANDLE hm;
			LPVOID lp;
			DWORD ThreadId = NULL;
			if (!(hm = OpenFileMappingA(FILE_MAP_ALL_ACCESS, true, NAMEE))) throw "open shared filemapping error";
			if (!(lp = MapViewOfFile(hm, FILE_MAP_ALL_ACCESS, 0, 0, 0))) throw "mapping file error";

			HTHANDLE* ht = new(lp) HTHANDLE;
			memcpy(ht->FileName, FileName, sizeof(ht->FileName));
			ht->FileMapping = hm;
			ht->Addr = lp; //

			return ht;
		}
		catch (const char* message)
		{
			return NULL;
		}
	}

	HTHANDLE* Open(const char FileName[512])
	{
		try
		{
			HANDLE hf, hm;
			LPVOID lp;
			DWORD ThreadId = NULL;

			if ((hf = CreateFileA(FileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)	throw "cannot open file";
			if (!(hm = CreateFileMappingA(hf, NULL, PAGE_READWRITE, 0, 0, NAMEE))) throw "create filemapping error";
			if (!(lp = MapViewOfFile(hm, FILE_MAP_ALL_ACCESS, 0, 0, 0))) throw "mapping file error";

			HTHANDLE* ht = new(lp) HTHANDLE(hf, hm, lp, FileName);

			if (!(ht->SnapThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SnapTimer, ht, 0, &ThreadId))) throw "cannot create snapshot thread";
			return ht;
		}
		catch (const char* message)
		{
			return NULL;
		}
	}


	BOOL Snap(HTHANDLE* hthandle)
	{
		try
		{
			if (hthandle == NULL) throw "snap: handle null";

			if (!FlushViewOfFile(hthandle->Addr, NULL))  throw "snap error";
			hthandle->lastsnaptime = time(NULL);

			cout << "snap completed" << endl;
			cout << hthandle->Addr << endl;

			return TRUE;
		}
		catch (const char* message)
		{
			SetLastError(hthandle, message);
			//cout << hthandle->Addr << endl;
			return FALSE;
		}
	}


	BOOL Close(const HTHANDLE* hthandle)  //выполнить Snap и закрыть HT - хранилище для использования
	{
		try
		{
			if (!Snap((HTHANDLE*)hthandle)) 				throw "error while snapping the file before closing";
			cout << "Snap before closing..." << endl;

			if (hthandle->SnapTimer)
			{
				if (!CancelWaitableTimer(hthandle->SnapTimer))	throw "cancelling timer error";
				if (!CloseHandle(hthandle->SnapTimer))			throw "closing timer handle error";
			}

			if (!TerminateThread(hthandle->SnapThread, 0))	throw "terminate thread error";
			if (!CloseHandle(hthandle->SnapThread))			throw "closing snapshot thread error";

			if (!CloseHandle(hthandle->File))				throw "closing file error";
			if (!CloseHandle(hthandle->FileMapping))		throw "closing mapping error";



			WaitForSingleObject(hthandle->Mutex, INFINITE);
			if (!CloseHandle(hthandle->Mutex))				throw "closing mutex error";

			if (!UnmapViewOfFile(hthandle->Addr))			throw "unmapping file error";

			return TRUE;
		}
		catch (const char* message)
		{
			cout << message << endl;
			SetLastError((HTHANDLE*)hthandle, message);
			return FALSE;
		}
	}


	BOOL Insert(HTHANDLE* hthandle, Element* newElement)
	{
		try
		{
			if (hthandle == NULL) throw "insert: handle null";
			if (newElement->keylength > hthandle->MaxKeyLength)			throw "too long key";
			if (newElement->payloadlength > hthandle->MaxPayloadLength)	throw "too long payload";

			WaitForSingleObject(hthandle->Mutex, INFINITE);

			bool b = false;
			if (hthandle->N != hthandle->Capacity)
			{
				for (int i = 0, j = Hash(newElement, hthandle->Capacity);
					i != hthandle->Capacity && !b;
					j = NextHash(j, hthandle->Capacity, ++i))
				{
					Element* element = GetByIndex(hthandle, j);
					if (element == NULL || DEL(element))
					{
						int size = SINGLE_ELEMENT_SIZE(hthandle);
						char* newElementPointer = (char*)(hthandle + 1) + size * j;

						memcpy(newElementPointer, newElement->key, newElement->keylength);

						newElementPointer += hthandle->MaxKeyLength;
						memcpy(newElementPointer, &newElement->keylength, sizeof(newElement->keylength));

						newElementPointer += sizeof(newElement->keylength);
						memcpy(newElementPointer, newElement->payload, newElement->payloadlength);

						newElementPointer += hthandle->MaxPayloadLength;
						memcpy(newElementPointer, &newElement->payloadlength, sizeof(newElement->payloadlength));

						hthandle->N++;
						b = true;
					}
					if (element != NULL && !memcmp(element->key, newElement->key, element->keylength))
					{
						ReleaseMutex(hthandle->Mutex);
						throw "insert: duplicate key";
					}
				}
			}
			ReleaseMutex(hthandle->Mutex);
			return b;
		}
		catch (const char* message)
		{
			SetLastError(hthandle, message);
			return FALSE;
		}
	}

	Element* Get(HTHANDLE* hthandle, Element* element)
	{
		try
		{
			if (hthandle == NULL) throw "get: handle null";
			WaitForSingleObject(hthandle->Mutex, INFINITE);

			int index = SearchIndex(hthandle, element);
			if (index < 0)
			{
				ReleaseMutex(hthandle->Mutex);
				throw "key not found";
			}

			ReleaseMutex(hthandle->Mutex);

			return GetByIndex(hthandle, index);
		}
		catch (const char* message)
		{
			SetLastError(hthandle, message);
			return NULL;
		}
	}


	BOOL Delete(HTHANDLE* hthandle, Element* element)
	{
		const int DELETED = -1;
		try {
			if (hthandle == NULL) throw "delete: handle null";

			WaitForSingleObject(hthandle->Mutex, INFINITE);

			int index = SearchIndex(hthandle, element);
			if (index < 0)
			{
				ReleaseMutex(hthandle->Mutex);
				throw "key not found";
			}

			Element* forDelete = GetByIndex(hthandle, index);

			//ZeroMemory(forDelete, SINGLE_ELEMENT_SIZE(hthandle));
			memcpy(forDelete->key, &DELETED, sizeof(DELETED));
			hthandle->N--;

			ReleaseMutex(hthandle->Mutex);

			return TRUE;
		}
		catch (const char* message)
		{
			SetLastError(hthandle, message);
			return FALSE;
		}
	}


	BOOL Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlength)
	{
		try
		{
			if (hthandle == NULL) throw "update: handle null";

			if (newpayloadlength > hthandle->MaxPayloadLength) throw "new payload length too long";

			WaitForSingleObject(hthandle->Mutex, INFINITE);

			int index = SearchIndex(hthandle, oldelement);
			if (index < 0)
			{
				ReleaseMutex(hthandle->Mutex);
				throw "key not found";
			}

			Element* forUpdate = GetByIndex(hthandle, index);

			ZeroMemory(forUpdate->payload, hthandle->MaxPayloadLength + sizeof(int));

			memcpy(forUpdate->payload, newpayload, newpayloadlength);
			memcpy((char*)forUpdate->payload + hthandle->MaxPayloadLength, &newpayloadlength, sizeof(oldelement->payloadlength));


			ReleaseMutex(hthandle->Mutex);
			return TRUE;
		}
		catch (const char* message)
		{
			SetLastError(hthandle, message);
			return FALSE;
		}
	}


	char* GetLastErrorHT(HTHANDLE* ht)
	{
		return ht->LastErrorMessage;
	}

	void print(const Element* element)
	{
		printf("key: %s, value: %s\n", element->key, element->payload);
	}
}