#include "pch.h"
#include "REGISTRY.h"
#include "INSTALL.h"
#include "REGISTRY.h"
#include "SEQLOG.h"
extern HMODULE hmodule;

STDAPI DllInstall(BOOL b, PCWSTR s) {
	SEQ;
	LOG("DllInstall ", (b) ? "install" : "uninstall");
	return S_OK;
}

STDAPI DllRegisterServer()
{
	SEQ;
	LOG("DllRegisterServer ", hmodule);
	HRESULT rc = RegisterServer(hmodule, CLSID_OS12, FNAME, VINDX, PGID);
	LOG("DLLRegisterServer rc = ", rc);
	return rc;
}

STDAPI DllUnregisterServer()
{
	SEQ;
	LOG("DllUnregister ", hmodule);
	HRESULT rc = UnregisterServer(CLSID_OS12, VINDX, PGID);
	LOG("DLLUnregisterServer rc = ", rc);
	return rc;
}
