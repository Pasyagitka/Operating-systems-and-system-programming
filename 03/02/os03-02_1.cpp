#include <iostream>
#include <process.h>
#include "Windows.h"

void main()
{
  std::cout << "03-02_1" << std::endl;
  for (int i=0; i<50;i++)
  {
    std::cout << getpid() << std::endl;
    Sleep(1000);
  }
}