#pragma once
#include <objbase.h>

#define FNAME L"ZEI.OS12.COM"
#define VINDX L"ZEI.OS12.1"
#define PGID L"ZEI.OS12"


// {A0CA645A-D0F2-4BA5-BB08-B5EA95C9068E}
static const GUID CLSID_OS12 = 
{ 0xa0ca645a, 0xd0f2, 0x4ba5, { 0xbb, 0x8, 0xb5, 0xea, 0x95, 0xc9, 0x6, 0x8e } };


// {D116FE7C-EA09-4E03-9E09-AE1F09BCC0C2}
static const GUID IID_IADDER =
{ 0xd116fe7c, 0xea09, 0x4e03, { 0x9e, 0x9, 0xae, 0x1f, 0x9, 0xbc, 0xc0, 0xc2 } };
interface IADDER :IUnknown
{
	virtual HRESULT __stdcall Add(const double x,const double y,double& z) = 0;
	virtual HRESULT __stdcall Sub(const double x,const double y,double& z) = 0;
};

//{9CF6CBD5 - 32DB - 489C - 86BE - 5E1241D44394}
static const GUID IID_IMULTIPLIER =
{ 0x9cf6cbd5, 0x32db, 0x489c, { 0x86, 0xbe, 0x5e, 0x12, 0x41, 0xd4, 0x43, 0x94 } };
interface IMULTIPLIER :IUnknown
{
	virtual HRESULT __stdcall Mul(const double x, const double y, double& z) = 0;
	virtual HRESULT __stdcall Div(const double x, const double y, double& z) = 0;
};

