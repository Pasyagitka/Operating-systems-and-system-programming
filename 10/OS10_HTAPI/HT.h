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
	// API HT - программный интерфейс для доступа к НТ-хранилищу 
	//          НТ-хранилище предназначено для хранения данных в ОП в формате ключ/значение
	//          Персистестеность (сохранность) данных обеспечивается с помощью snapshot-менханизма 
	//          Create - создать  и открыть HT-хранилище для использования   
	//          Open   - открыть HT-хранилище для использования
	//          Insert - создать элемент данных
	//          Delete - удалить элемент данных    
	//          Get    - читать  элемент данных
	//          Update - изменить элемент данных
	//          Snap   - выпонить snapshot
	//          Close  - выполнить Snap и закрыть HT-хранилище для использования
	//          GetLastError - получить сообщение о последней ошибке

	struct HTHANDLE    // блок управления HT
	{
		HTHANDLE();
		HTHANDLE(HANDLE hf, HANDLE hm, LPVOID lp, const char FileName[512]);
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]);
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512], HANDLE hf, HANDLE hm, LPVOID lp);
		int     Capacity;               // емкость хранилища в количестве элементов 
		int     SecSnapshotInterval;    // переодичность сохранения в сек. 
		int     MaxKeyLength;           // максимальная длина ключа
		int     MaxPayloadLength;       // максимальная длина данных
		char    FileName[512];          // имя файла 
		HANDLE  File;                   // File HANDLE != 0, если файл открыт
		HANDLE  FileMapping;            // Mapping File HANDLE != 0, если mapping создан  
		LPVOID  Addr;                   // Addr != NULL, если mapview выполнен  
		char    LastErrorMessage[512];  // сообщение об последней ошибке или 0x00  
		time_t  lastsnaptime;           // дата последнего snap'a (time())  

		int N;
		HANDLE Mutex;
		HANDLE SnapThread;
		HANDLE SnapTimer;
	};

	struct Element   // элемент 
	{
		Element();
		Element(const void* key, int keylength);											  // for Get
		Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
		Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for Update
		void* key;                 // значение ключа 
		int   keylength;           // рахмер ключа
		void* payload;             // данные 
		int   payloadlength;       // размер данных
	};


	HTHANDLE* Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512]); 	// переодичность сохранения в сек.
	// != NULL успешное завершение  

	HTHANDLE* Open(const char FileName[512]);
	// != NULL успешное завершение  

	BOOL Snap(HTHANDLE* hthandle);								// управление HT (File, FileMapping)

	// Snap и закрыть HT  и  очистить HTHANDLE
	BOOL Close(const HTHANDLE* hthandle);						// управление HT (File, FileMapping)
	//  == TRUE успешное завершение   

	BOOL Insert(HTHANDLE* hthandle, Element* element);			// управление HT, элемент
	//  == TRUE успешное завершение 

	BOOL Delete(HTHANDLE* hthandle, Element* element);			// управление HT (ключ),  элемент 
	//  == TRUE успешное завершение 

	Element* Get(HTHANDLE* hthandle, Element* element); 		//управление HT, элемент 
	//  != NULL успешное завершение 

	BOOL Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlength); 		// управление HT, старый элемент (ключ, размер ключа)
	//  == TRUE успешное завершение 


	// получить сообщение о последней ошибке
	char* GetLastError(HTHANDLE* ht);                         // управление HT

	// распечатать элемент 
	void print(const Element* element);						// элемент 
};
