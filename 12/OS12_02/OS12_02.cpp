#include <objbase.h>
#include <iostream>


// {A0CA645A-D0F2-4BA5-BB08-B5EA95C9068E}
static const GUID CLSID_OS12 =
{ 0xa0ca645a, 0xd0f2, 0x4ba5, { 0xbb, 0x8, 0xb5, 0xea, 0x95, 0xc9, 0x6, 0x8e } };

// {D116FE7C-EA09-4E03-9E09-AE1F09BCC0C2}
static const GUID IID_IADDER =
{ 0xd116fe7c, 0xea09, 0x4e03, { 0x9e, 0x9, 0xae, 0x1f, 0x9, 0xbc, 0xc0, 0xc2 } };
interface IADDER :IUnknown
{
	virtual HRESULT __stdcall Add(const double x, const double y, double& z) = 0;
	virtual HRESULT __stdcall Sub(const double x, const double y, double& z) = 0;
};

//{9CF6CBD5 - 32DB - 489C - 86BE - 5E1241D44394}
static const GUID IID_IMULTIPLIER =
{ 0x9cf6cbd5, 0x32db, 0x489c, { 0x86, 0xbe, 0x5e, 0x12, 0x41, 0xd4, 0x43, 0x94 } };
interface IMULTIPLIER :IUnknown
{
	virtual HRESULT __stdcall Mul(const double x, const double y, double& z) = 0;
	virtual HRESULT __stdcall Div(const double x, const double y, double& z) = 0;
};


#define IERR(s)    std::cout<<"error "<<s<<std::endl
#define IRES(s,r)  std::cout<<s<<r<<std::endl

IADDER* pIAdder = nullptr;
IMULTIPLIER* pMultiplier = nullptr;



int main()
{
	IUnknown* pIUnknown = NULL;
	CoInitialize(NULL);                        // инициализация библиотеки OLE32
	HRESULT hr0 = CoCreateInstance(CLSID_OS12, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
	if (SUCCEEDED(hr0))
	{
		std::cout << "CoCreateInstance succeeded" << std::endl;
		if (SUCCEEDED(pIUnknown->QueryInterface(IID_IADDER, (void**)&pIAdder)))
		{
			{
				double z = 0.0;
				if (!SUCCEEDED(pIAdder->Add(2.0, 3.0, z)))  IERR("IAdder::Add");
				else IRES("IAdder::Add = ", z);
			}
			{
				double z = 0.0;
				if (!SUCCEEDED(pIAdder->Sub(2.0, 3.0, z)))  IERR("IAdder::Sub");
				else IRES("IAdder::Sub = ", z);
			}
			if (SUCCEEDED(pIAdder->QueryInterface(IID_IMULTIPLIER, (void**)&pMultiplier)))
			{
				{
					double z = 0.0;
					if (!SUCCEEDED(pMultiplier->Mul(2.0, 3.0, z))) IERR("IMultiplier::Mul");
					else IRES("Multiplier::Mul = ", z);
				}
				{
					double z = 0.0;
					if (!SUCCEEDED(pMultiplier->Div(2.0, 3.0, z))) IERR("IMultiplier::Div");
					else IRES("IMultiplier::Div = ", z);
				}
				if (SUCCEEDED(pMultiplier->QueryInterface(IID_IADDER, (void**)&pIAdder)))
				{
					double z = 0.0;
					if (!SUCCEEDED(pIAdder->Add(2.0, 3.0, z))) IERR("IAdder::Add");
					else IRES("IAdder::Add = ", z);
					pIAdder->Release();
				}
				else  IERR("IMultiplier->IAdder");
				pMultiplier->Release();
			}
			else IERR("IAdder->IMultiplier");
			pIAdder->Release();
		}
		else  IERR("IAdder");
	}
	else  std::cout << "CoCreateInstance error" << std::endl;
	pIUnknown->Release();
	CoFreeUnusedLibraries();                   // завершение работы с библиотекой      

	return 0;
}