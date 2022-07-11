#pragma once
#include <objbase.h>
#include <iostream>
#include "INTERFACE.h"
#include <string>
#include "HT.h"

class HT_COM: public IHT
{
public:
	HT_COM();
	~HT_COM();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual HRESULT STDMETHODCALLTYPE Create(HT::HTHANDLE** result, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, char FileName[512]);

	virtual HRESULT STDMETHODCALLTYPE Open(HT::HTHANDLE** result, char FileName[512]);
	virtual HRESULT STDMETHODCALLTYPE OpenShared(HT::HTHANDLE** result, char FileName[512]);
	virtual HRESULT STDMETHODCALLTYPE Snap(HT::HTHANDLE**  hthandle);

	virtual HRESULT STDMETHODCALLTYPE Close(HT::HTHANDLE** hthandle);
	virtual HRESULT STDMETHODCALLTYPE Insert(HT::HTHANDLE**  hthandle, HT::Element* element);
	virtual HRESULT STDMETHODCALLTYPE Update(HT::HTHANDLE**  hthandle, HT::Element* oldelement, void* newpayload, int newpayloadlength);
	virtual HRESULT STDMETHODCALLTYPE Delete(HT::HTHANDLE** hthandle, HT::Element* element);

	virtual HRESULT STDMETHODCALLTYPE GetLastErrorHT(char** error, HT::HTHANDLE** ht);

	virtual HRESULT STDMETHODCALLTYPE Get(HT::Element& result, HT::HTHANDLE** hthandle, HT::Element* element);
	virtual HRESULT STDMETHODCALLTYPE GetElement(HT::Element** result, const void* key, int keylength, const void* payload, int payloadlength);


private:
	volatile ULONG m_Ref;
};
