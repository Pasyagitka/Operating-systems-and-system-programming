#include <iostream>
#include <time.h>
#include <ctime>

using namespace std;

int main()
{
    time_t t1 = time(NULL);
	tm ttm;
	localtime_s(&ttm, &t1);
    printf_s("%d.%d.%d %d:%d:%d", ttm.tm_mday, ttm.tm_mon + 1, ttm.tm_year + 1900, ttm.tm_hour, ttm.tm_min, ttm.tm_sec);
}