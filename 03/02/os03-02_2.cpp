#include <iostream>
#include <process.h>
#include "Windows.h"

void main()
{
  std::cout << "03-02_2" << std::endl;
  for (int i=0; i<125;i++)
  {
    std::cout << getpid() << std::endl;
    Sleep(1000);
  }
}