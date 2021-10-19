#include <iostream>
#include <process.h>
#include "Windows.h"

void main()
{
  for (int i=0; i<1000;i++)
  {
    std::cout << getpid() << std::endl;
    Sleep(1000);
  }
}