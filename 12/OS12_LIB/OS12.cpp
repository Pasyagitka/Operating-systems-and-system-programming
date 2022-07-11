#include "pch.h"
#include "framework.h"
#include "OS12.h"

namespace OS12
{
	OS12HANDEL Init() 
	{
		IUnknown* pIUnknown = NULL;
		CoInitialize(NULL);                        // инициализация библиотеки OLE32
		HRESULT hr = CoCreateInstance(CLSID_OS12, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
		if (!SUCCEEDED(hr)) throw (int)hr;
		return pIUnknown;
	}

	void Dispose(OS12HANDEL h) 
	{
		IUnknown* pIUnknown = static_cast<IUnknown*>(h);
		pIUnknown->Release();
		CoFreeUnusedLibraries();
	}

	namespace ADDER 
	{
		double Add(OS12HANDEL h, double x, double y) 
		{
			IUnknown* pIUnknown = static_cast<IUnknown*>(h);
			IADDER* pIAdder = nullptr;
			HRESULT hr = pIUnknown->QueryInterface(IID_IADDER, (void**)&pIAdder);
			if (!SUCCEEDED(hr)) throw (int)hr;
			double z = 0.0;
			hr = pIAdder->Add(x, y, z);
			pIAdder->Release();
			if (!SUCCEEDED(hr)) throw (int)hr;
			else return z;
		}

		double Sub(OS12HANDEL h, double x, double y) 
		{
			IUnknown* pIUnknown = static_cast<IUnknown*>(h);
			IADDER* pIAdder = nullptr;
			HRESULT hr = pIUnknown->QueryInterface(IID_IADDER, (void**)&pIAdder);
			if (!SUCCEEDED(hr)) throw (int)hr;
			double z = 0.0;
			hr = pIAdder->Sub(x, y, z);
			pIAdder->Release();
			if (!SUCCEEDED(hr)) throw (int)hr;
			else return z;
		}
	}

	namespace MULTIPLIER 
	{
		double Mul(OS12HANDEL h, double x, double y) 
		{
			IUnknown* pIUnknown = static_cast<IUnknown*>(h);
			IMULTIPLIER* pIMultiplier = nullptr;
			HRESULT hr = pIUnknown->QueryInterface(IID_IMULTIPLIER, (void**)&pIMultiplier);
			if (!SUCCEEDED(hr)) throw (int)hr;
			double z = 0.0;
			hr = pIMultiplier->Mul(x, y, z);
			pIMultiplier->Release();
			if (!SUCCEEDED(hr)) throw (int)hr;
			else return z;
		}

		double Div(OS12HANDEL h, double x, double y) 
		{
			if (y == 0) throw "DivideByZeroException";
			IUnknown* pIUnknown = static_cast<IUnknown*>(h);
			IMULTIPLIER* pIMultiplier = nullptr;
			HRESULT hr = pIUnknown->QueryInterface(IID_IMULTIPLIER, (void**)&pIMultiplier);
			if (!SUCCEEDED(hr)) throw (int)hr;
			double z = 0.0;
			hr = pIMultiplier->Mul(x, y, z);
			pIMultiplier->Release();
			if (!SUCCEEDED(hr)) throw (int)hr;
			else return z;
		}
	}
}