#pragma once
#include <Windows.h>
#include <string.h>
#include <iostream>
#include<iomanip>

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

	struct HTHANDLE    // ���� ���������� HT
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

	struct Element   // ������� 
	{
		Element();
		Element(const void* key, int keylength);											  // for Get
		Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
		Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for Update
		void* key;                 // �������� ����� 
		int   keylength;           // ������ �����
		void* payload;             // ������ 
		int   payloadlength;       // ������ ������
	};


	HTHANDLE* Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]); 	// ������������� ���������� � ���.
	// != NULL �������� ����������  

	HTHANDLE* Open(const char FileName[512]);
	// != NULL �������� ����������  

	BOOL Snap(HTHANDLE* hthandle);								// ���������� HT (File, FileMapping)

	// Snap � ������� HT  �  �������� HTHANDLE
	BOOL Close(const HTHANDLE* hthandle);						// ���������� HT (File, FileMapping)
	//  == TRUE �������� ����������   

	BOOL Insert(HTHANDLE* hthandle, Element* element);			// ���������� HT, �������
	//  == TRUE �������� ���������� 

	BOOL Delete(HTHANDLE* hthandle, Element* element);			// ���������� HT (����),  ������� 
	//  == TRUE �������� ���������� 

	Element* Get(HTHANDLE* hthandle, Element* element); 		//���������� HT, ������� 
	//  != NULL �������� ���������� 

	BOOL Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlength); 		// ���������� HT, ������ ������� (����, ������ �����)
	//  == TRUE �������� ���������� 


	// �������� ��������� � ��������� ������
	char* GetLastError(HTHANDLE* ht);                         // ���������� HT

	// ����������� ������� 
	void print(const Element* element);						// ������� 
};
