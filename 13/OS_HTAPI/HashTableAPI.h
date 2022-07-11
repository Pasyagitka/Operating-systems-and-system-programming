#pragma once
#include <Windows.h>
#include "../OS_HTCOM/HT.h"

namespace HTAPI
{
	bool OpenApi();
	bool CloseApi();

	HT::HTHANDLE * Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, char FileName[512]);

	HT::HTHANDLE* Open(char FileName[512]);
	HT::HTHANDLE* OpenShared(char FileName[512]);

	BOOL Snap(HT::HTHANDLE * hthandle);

	BOOL Close(HT::HTHANDLE * hthandle);

	BOOL Insert(HT::HTHANDLE * hthandle, HT::Element* element);
	BOOL Delete(HT::HTHANDLE * hthandle, HT::Element* element);
	BOOL Update(HT::HTHANDLE * hthandle, HT::Element * oldelement, void* newpayload, int newpayloadlength);

	HT::Element* Get(HT::HTHANDLE * hthandle, HT::Element * element);

	char* GetLastErrorHT(HT::HTHANDLE * ht);

	HT::Element* GetElement(const void* key, int keylength, const void* payload, int  payloadlength);
};
