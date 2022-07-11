#include "HT.h"
using namespace std;

namespace HT
{
	Element::Element()
	{
		this->key = nullptr;
		this->keylength = 0;
		this->payload = nullptr;
		this->payloadlength = 0;
	}

	Element::Element(const void* key, int keylength)										  // for Get
	{
		this->key = (void*)key;
		this->keylength = keylength;
		this->payload = nullptr;
		this->payloadlength = 0;
	}

	Element::Element(const void* key, int keylength, const void* payload, int payloadlength)  // for Insert
	{
		this->key = (void*)key;
		this->keylength = keylength;
		this->payload = (void*)payload;
		this->payloadlength = payloadlength;
	}

	Element::Element(Element* oldelement, const void* newpayload, int newpayloadlength)		 // for Update
	{
		this->key = oldelement->key;
		this->keylength = oldelement->keylength;
		this->payload = (void*)newpayload;
		this->payloadlength = newpayloadlength;
	}
}

