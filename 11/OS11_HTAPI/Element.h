#pragma once

#ifdef HTAPI_EXPORTS
#define HT_API __declspec(dllexport)
#else
#define HT_API __declspec(dllimport)
#endif


namespace HT 
{
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

	extern "C" HT_API Element* getElement(const void* key, int keylength, const void* payload, int  payloadlength);
}