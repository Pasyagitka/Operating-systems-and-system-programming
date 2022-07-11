#include <Windows.h>
#include <objbase.h>
#include "HashTableAPI.h"
#include "../OS_HTCOM/INTERFACE.h"
#include <iostream>

namespace HTAPI
{
	IHT* pIHashTable = nullptr;
	IUnknown* pIUnknown = NULL;

	bool  HTAPI::OpenApi() 
	{
		CoInitialize(NULL);                        // инициализация библиотеки OLE32
		HRESULT hr0 = CoCreateInstance(CLSID_CA, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
		if (SUCCEEDED(hr0))
		{
			std::cout << "CoCreateInstance succeeded" << std::endl;
			if (SUCCEEDED(pIUnknown->QueryInterface(IID_IHashTable, (void**)&pIHashTable)))
			{
				return true;
			}
		}
		return false;
	}

	bool  HTAPI::CloseApi() 
	{
		bool res = true;
		if (!SUCCEEDED(pIHashTable->Release()))
			res = false;
		if (!SUCCEEDED(pIUnknown->Release()))
			res = false;
		CoFreeUnusedLibraries();
		return true;
	}


	HT::HTHANDLE* HTAPI::Create(int Capacity, int   SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, char FileName[512]) 
	{
		HT::HTHANDLE* pht;
		if (SUCCEEDED(pIHashTable->Create(&pht, Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, FileName))) 
		{
			return pht;
		}
		else 
		{
			return NULL;
		}
	}
	HT::HTHANDLE* HTAPI::Open(char FileName[512]) 
	{
		HT::HTHANDLE* pht;
	
		if (SUCCEEDED(pIHashTable->Open(&pht, FileName))) 
		{
			return pht;
		}
		else 
		{
			return NULL;
		}
	}

	HT::HTHANDLE* HTAPI::OpenShared(char FileName[512])
	{
		HT::HTHANDLE* pht;

		if (SUCCEEDED(pIHashTable->OpenShared(&pht, FileName)))
		{
			return pht;
		}
		else
		{
			return NULL;
		}
	}

	BOOL Snap(HT::HTHANDLE* hthandle)
	{
		if (SUCCEEDED(pIHashTable->Snap(&hthandle))) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}


	BOOL Close(HT::HTHANDLE* hthandle) 
	{
		if (SUCCEEDED(pIHashTable->Close(&hthandle))) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}


	BOOL Insert(HT::HTHANDLE* hthandle, HT::Element* element) 
	{
		if (SUCCEEDED(pIHashTable->Insert(&hthandle, element))) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}


	BOOL Delete (HT::HTHANDLE* hthandle, HT::Element* element) 
	{
		if (SUCCEEDED(pIHashTable->Delete(&hthandle, element))) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	HT::Element* Get(HT::HTHANDLE* hthandle, HT::Element* element) 
	{
		HT::Element result = *GetElement("key", 4, "0", 4);
		if (SUCCEEDED(pIHashTable->Get(result, &hthandle, element)))
		{
			return &result;
		}
		else 
		{
			return NULL;
		}
	}



	BOOL Update(HT::HTHANDLE* hthandle, HT::Element* oldelement, void* newpayload, int newpayloadlength) 
	{
		if (SUCCEEDED(pIHashTable->Update(&hthandle, oldelement, newpayload, newpayloadlength))) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	char* GetLastErrorHT(HT::HTHANDLE* ht) 
	{
		char* err;
		if (SUCCEEDED(pIHashTable->GetLastErrorHT(&err, &ht))) 
		{
			return err;
		}
		else 
		{
			return NULL;
		}
	}


	HT::Element* GetElement(const void* key, int keylength, const void* payload, int  payloadlength)
	{
		HT::Element* result;
		
		if (SUCCEEDED(pIHashTable->GetElement(&(result), key, keylength, payload, payloadlength))) {
			return result;
		}
		else
		{
			return NULL;
		}
	}

};
