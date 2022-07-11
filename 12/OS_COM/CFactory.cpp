#include "pch.h"
#include "CFactory.h"
#include "OS12.h"
#include "SEQLOG.h"

HRESULT STDMETHODCALLTYPE CFactory::CreateInstance(IUnknown* pUO, const IID& id, void **ppv)
{
	SEQ;
	HRESULT rc = E_UNEXPECTED;
	OS12* pA;
	if (pUO != NULL) rc = CLASS_E_NOAGGREGATION;
	else if ((pA = new OS12()) == NULL) rc = E_OUTOFMEMORY;
	else {
		rc = pA->QueryInterface(id, ppv);
		pA->Release();
	}
	LOG("CFactory::CreateInstance rc = ", rc);
	return rc;
}

HRESULT STDMETHODCALLTYPE CFactory::LockServer(BOOL b)
{
	SEQ;
	HRESULT rc = S_OK;
	LOG("CFactory::LockServer rc = ", rc);
	return rc;
}

CFactory::CFactory() :m_Ref(1) {
	SEQ;
	LOG("CFactory::CFactory", "");
};

CFactory::~CFactory() {
	SEQ;
	LOG("CFactory::~CFactory", "");
};

HRESULT STDMETHODCALLTYPE CFactory::QueryInterface(REFIID riid, void** ppv)
{
	SEQ;
	HRESULT rc = S_OK;
	*ppv = NULL;
	if (riid == IID_IUnknown)			*ppv = static_cast<IUnknown*>(this);
	else if (riid == IID_IClassFactory) *ppv = static_cast<IClassFactory*>(this);
	else rc = E_NOINTERFACE;
	if (rc == S_OK) this->AddRef();
	LOG("CFactory::QueryInterface rc =", rc);
	return rc;
};

ULONG STDMETHODCALLTYPE CFactory::AddRef(void)
{
	SEQ;
	InterlockedIncrement((LONG*)&(this->m_Ref));
	LOG("CFactory::AddRef rc = ", this->m_Ref);
	return this->m_Ref;
};

ULONG STDMETHODCALLTYPE CFactory::Release(void)
{
	SEQ;
	ULONG  rc = this->m_Ref;
	if ((rc = InterlockedDecrement((LONG*)&(this->m_Ref))) == 0) delete this;
	LOG("CFactory::Release rc = ", this->m_Ref);
	return this->m_Ref;
};
