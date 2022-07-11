#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>


#define HT_CALL_CONV __declspec(dllexport)

//#ifdef HTAPI_EXPORTS
//#define HT_API __declspec(dllexport)
//#else
#define HT_API __declspec(dllexport)
//#endif


#define CREATE_HTFILE_ERROR "Create HTFile error";
#define CREATE_FILEMAPPING_ERROR "Create FileMapping error";
#define MAPPING_VIEW_ERROR "Mapping view failed";

#define SINGLE_ELEMENT_SIZE(hthandle) (hthandle->MaxKeyLength + hthandle->MaxPayloadLength + 2 * sizeof(int))
#define HT_SIZE(hthandle) (sizeof(HTHANDLE) + Capacity * (MaxKeyLength + MaxPayloadLength + 2 * sizeof(int)))


namespace HT
{
	extern "C" HT_API  struct HTHANDLE
	{
		HTHANDLE();
		HTHANDLE(HANDLE hf, HANDLE hm, LPVOID lp, const char FileName[512]);
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]);
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512], HANDLE hf, HANDLE hm, LPVOID lp);
		int     Capacity;               // ������� ��������� � ���������� ��������� 
		int     SecSnapshotInterval;    // ������������� ���������� � ���. 
		int     MaxKeyLength;           // ������������ ����� �����
		int     MaxPayloadLength;       // ������������ ����� ������
		char    FileName[512];          // ��� ����� 
		HANDLE  File;                   // File HANDLE != 0, ���� ���� ������
		HANDLE  FileMapping;            // Mapping File HANDLE != 0, ���� mapping ������  
		LPVOID  Addr;                   // Addr != NULL, ���� mapview ��������  
		char    LastErrorMessage[512];  // ��������� �� ��������� ������ ��� 0x00  
		time_t  lastsnaptime;           // ���� ���������� snap'a (time())  

		int N;
		HANDLE Mutex;
		HANDLE SnapThread;
		HANDLE SnapTimer;
	};

	extern "C" HT_API struct Element   // ������� 
	{
		HT_API Element();
		HT_API Element(const void* key, int keylength);											  // for Get
		HT_API Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
		HT_API Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for Update
		void* key;                 // �������� ����� 
		int   keylength;           // ������ �����
		void* payload;             // ������ 
		int   payloadlength;       // ������ ������
	};

	extern "C" HT_API HTHANDLE * Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]); 	// ������������� ���������� � ���.
	extern "C" HT_API HTHANDLE * OpenShared(const char FileName[512]);
	extern "C" HT_API HTHANDLE * Open(const char FileName[512]);
	extern "C" HT_API BOOL Snap(HTHANDLE * hthandle);								// ���������� HT (File, FileMapping)
	extern "C" HT_API BOOL Close(const HTHANDLE * hthandle);						// ���������� HT (File, FileMapping)
	extern "C" HT_API BOOL Insert(HTHANDLE * hthandle, Element * element);			// ���������� HT, �������
	extern "C" HT_API BOOL Delete(HTHANDLE * hthandle, Element * element);			// ���������� HT (����),  ������� 
	extern "C" HT_API Element * Get(HTHANDLE * hthandle, Element * element); 		//���������� HT, ������� 
	extern "C" HT_API Element * GetElement(const void* key, int keylength, const void* payload, int  payloadlength);


	extern "C" HT_API BOOL Update(HTHANDLE * hthandle, Element * oldelement, void* newpayload, int newpayloadlength); 		// ���������� HT, ������ ������� (����, ������ �����)
	
	extern "C" HT_API char* GetLastErrorHT(HTHANDLE * ht);                         // ���������� HT
	extern "C" HT_API void print(const Element * element);						// ������� 
};
