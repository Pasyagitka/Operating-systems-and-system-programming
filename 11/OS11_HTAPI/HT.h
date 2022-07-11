#pragma once
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include "Element.h"


#ifdef HTAPI_EXPORTS
#define HT_API __declspec(dllexport)
#else
#define HT_API __declspec(dllimport)
#endif


#define CREATE_HTFILE_ERROR "Create HTFile error";
#define CREATE_FILEMAPPING_ERROR "Create FileMapping error";
#define MAPPING_VIEW_ERROR "Mapping view failed";

#define SINGLE_ELEMENT_SIZE(hthandle) (hthandle->MaxKeyLength + hthandle->MaxPayloadLength + 2 * sizeof(int))
#define HT_SIZE(hthandle) (sizeof(HTHANDLE) + Capacity * (MaxKeyLength + MaxPayloadLength + 2 * sizeof(int)))

namespace HT    // HT API
{
	// API HT - ����������� ��������� ��� ������� � ��-��������� 
	//          ��-��������� ������������� ��� �������� ������ � �� � ������� ����/��������
	//          ���������������� (�����������) ������ �������������� � ������� snapshot-���������� 
	//          Create - �������  � ������� HT-��������� ��� �������������   
	//          Open   - ������� HT-��������� ��� �������������
	//          Insert - ������� ������� ������
	//          Delete - ������� ������� ������    
	//          Get    - ������  ������� ������
	//          Update - �������� ������� ������
	//          Snap   - �������� snapshot
	//          Close  - ��������� Snap � ������� HT-��������� ��� �������������
	//          GetLastError - �������� ��������� � ��������� ������

	extern "C" HT_API  struct HTHANDLE    // ���� ���������� HT
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


	extern "C" HT_API HTHANDLE * Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]); 	// ������������� ���������� � ���.
	// != NULL �������� ����������  

	extern "C" HT_API HTHANDLE* Open(const char FileName[512]);
	// != NULL �������� ����������  

	extern "C" HT_API HTHANDLE * OpenShared(const char MappingName[512]);
	//// != NULL �������� ����������  


	extern "C" HT_API BOOL Snap(HTHANDLE* hthandle);								// ���������� HT (File, FileMapping)

	// Snap � ������� HT  �  �������� HTHANDLE
	extern "C" HT_API BOOL Close(const HTHANDLE* hthandle);						// ���������� HT (File, FileMapping)
	//  == TRUE �������� ����������   

	extern "C" HT_API BOOL Insert(HTHANDLE* hthandle, Element* element);			// ���������� HT, �������
	//  == TRUE �������� ���������� 

	extern "C" HT_API BOOL Delete(HTHANDLE* hthandle, Element* element);			// ���������� HT (����),  ������� 
	//  == TRUE �������� ���������� 

	extern "C" HT_API Element* Get(HTHANDLE* hthandle, Element* element); 		//���������� HT, ������� 
	//  != NULL �������� ���������� 

	extern "C" HT_API BOOL Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlength); 		// ���������� HT, ������ ������� (����, ������ �����)
	//  == TRUE �������� ���������� 


	// �������� ��������� � ��������� ������
	extern "C" HT_API char* GetLastErrorHT(HTHANDLE * ht);                         // ���������� HT

	// ����������� ������� 
	extern "C" HT_API void print(const Element* element);						// ������� 
};
