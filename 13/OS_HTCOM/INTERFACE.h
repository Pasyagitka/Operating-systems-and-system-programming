#pragma once
#include <objbase.h>
#include "INTERFACE.h"
#include "HT.h"
#include <string>

#define FNAME L"ZEI.OS13.COM"
#define VINDX L"ZEI.OS13.1"
#define PGID L"ZEI.OS13"

// {E4D092DC-7F52-47FC-BA28-98FBF3FB9BA8}
static GUID CLSID_CA =
{ 0xe4d092dc, 0x7f52, 0x47fc, { 0xba, 0x28, 0x98, 0xfb, 0xf3, 0xfb, 0x9b, 0xa8 } };

// {A80051B5-4519-4635-A1B4-D3FBC32D1E2E}
static GUID IID_IHashTable =
{ 0xa80051b5, 0x4519, 0x4635, { 0xa1, 0xb4, 0xd3, 0xfb, 0xc3, 0x2d, 0x1e, 0x2e } };

interface IHT :IUnknown
{
	virtual HRESULT __stdcall Create(HT::HTHANDLE** result, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, char FileName[512]) = 0;

	virtual HRESULT __stdcall Open(HT::HTHANDLE** result, char FileName[512]) = 0;
	virtual HRESULT __stdcall OpenShared(HT::HTHANDLE** result, char FileName[512]) = 0;

	virtual HRESULT __stdcall Snap(HT::HTHANDLE** hthandle) = 0;

	virtual HRESULT __stdcall Close(HT::HTHANDLE** hthandle) = 0;

	virtual HRESULT __stdcall Insert(HT::HTHANDLE** hthandle, HT::Element* element) = 0;
	virtual HRESULT __stdcall Delete(HT::HTHANDLE** hthandle, HT::Element* element) = 0;
	virtual HRESULT __stdcall Update(HT::HTHANDLE** hthandle, HT::Element* oldelement, void* newpayload, int newpayloadlength) = 0;

	virtual HRESULT __stdcall GetLastErrorHT(char** error, HT::HTHANDLE** ht) = 0;

	virtual HRESULT __stdcall Get(HT::Element& result, HT::HTHANDLE** hthandle, HT::Element* element) = 0;
	virtual HRESULT __stdcall GetElement(HT::Element** result, const void* key, int keylength, const void* payload, int payloadlength) = 0;

};
