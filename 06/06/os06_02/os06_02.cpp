#include <Windows.h>
#include <iostream>

void main()
{
	for (int i = 0; i < 100000; i++)
	{
		std::cout << "i = " << i << std::endl;
		Sleep(1000);
	}
}