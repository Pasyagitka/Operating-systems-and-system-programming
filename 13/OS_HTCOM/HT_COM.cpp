#include "HT_COM.h"
#include "Seq_Log.h"
#include "HT.h"
#include <string>

extern ULONG g_Components;


HT_COM::HT_COM() :m_Ref(1)
{
	SEQ;
	InterlockedIncrement((LONG*)&g_Components);
	LOG("HT_COM::Adder g_Components = ", g_Components);
};

HT_COM::~HT_COM() 
{
	SEQ;
	InterlockedDecrement((LONG*)&g_Components);
	LOG("HT_COM::~Adder g_Components = ", g_Components);
};


HRESULT STDMETHODCALLTYPE HT_COM::QueryInterface(REFIID riid, void** ppv)
{
	SEQ;
	HRESULT rc = S_OK;
	*ppv = NULL;
	if (riid == IID_IUnknown)	*ppv = (IHT*)this;
	else if (riid == IID_IHashTable)	*ppv = (IHT*)this;
	else rc = E_NOINTERFACE;

	if (rc == S_OK) this->AddRef();
	LOG("HT_COM::QueryInterface rc = ", rc);
	return rc;
};

ULONG STDMETHODCALLTYPE HT_COM::AddRef(void) 
{
	SEQ;
	InterlockedIncrement((LONG*)&(this->m_Ref));
	LOG("HT_COM::AddRef m_Ref = ", this->m_Ref);
	return this->m_Ref;
};

ULONG STDMETHODCALLTYPE HT_COM::Release(void) 
{
	SEQ;

	ULONG rc = this->m_Ref;
	if ((rc = InterlockedDecrement((LONG*)&(this->m_Ref))) == 0) delete this;
	LOG("HT_COM::Release rc = ", rc);
	return rc;
};



HRESULT STDMETHODCALLTYPE HT_COM::Create(HT::HTHANDLE** result, int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, char FileName[512])
{
	*result = HT::Create(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, FileName);

	SEQ;
	LOG("Created ht result: ", &result);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE HT_COM::Open(HT::HTHANDLE** result, char FileName[512])
{
	HT::HTHANDLE* temp = HT::Open(FileName);
	if (temp == NULL)
		return E_FAIL;
	*result = temp;
	if (*result != NULL)
		return S_OK;
	else
		return E_FAIL;
}

HRESULT STDMETHODCALLTYPE HT_COM::OpenShared(HT::HTHANDLE** result, char FileName[512])
{
	HT::HTHANDLE* temp = HT::OpenShared(FileName);
	if (temp == NULL)
		return E_FAIL;
	*result = temp;
	if (*result != NULL)
		return S_OK;
	else
		return E_FAIL;
}

HRESULT STDMETHODCALLTYPE HT_COM::Snap(HT::HTHANDLE**  hthandle)
{
	if (HT::Snap(*hthandle))
		return S_OK;
	else
		return E_FAIL;
}


HRESULT STDMETHODCALLTYPE HT_COM::Close(HT::HTHANDLE** hthandle)
{
	bool res = HT::Close(*hthandle);

	if (res)
		return S_OK;
	else
		return E_FAIL;
}


HRESULT STDMETHODCALLTYPE HT_COM::Insert (HT::HTHANDLE**  hthandle, HT::Element* element)
{
	if (HT::Insert(*hthandle, element))
		return S_OK;
	else
		return E_FAIL;
}

HRESULT STDMETHODCALLTYPE HT_COM::Delete(HT::HTHANDLE**  hthandle, HT::Element* element)
{
	if (HT::Delete(*hthandle, element))
		return S_OK;
	else
		return E_FAIL;
}

HRESULT STDMETHODCALLTYPE HT_COM::Get(HT::Element& result, HT::HTHANDLE** hthandle, HT::Element* element)
{
	SEQ;
	HT::Element* temp = HT::Get(*hthandle, element);
	LOG("Get element with temp: ", temp);
	if (temp == NULL)
		return E_FAIL;
	result = *temp;

	return S_OK;
}


HRESULT STDMETHODCALLTYPE HT_COM::Update(HT::HTHANDLE**  hthandle, HT::Element* oldelement, void* newpayload, int newpayloadlength)
{
	if (HT::Update(*hthandle, oldelement, newpayload, newpayloadlength))
		return S_OK;
	else
		return E_FAIL;
}

 HRESULT STDMETHODCALLTYPE HT_COM::GetLastErrorHT(char** error, HT::HTHANDLE**  ht) 
 {
	 *error = (HT::GetLastErrorHT(*ht));

	 //error = std::string(HT::GetLastErrorHT(*ht));
	 //LOG("Ht error:  ", error);
	 return S_OK;
 }

 HRESULT STDMETHODCALLTYPE HT_COM::GetElement(HT::Element** result, const void* key, int keylength, const void* payload, int payloadlength)
 {
	 HT::Element* el = new HT::Element(key, keylength, payload, payloadlength);
	 if (el == NULL)
		 return E_FAIL;
	 *result = el;
	 return S_OK;
 }

