#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	printf("%d\n", getpid());
	for (int i = 0; i < 1000; i++)
	{
		sleep(1);
		printf("%d\n", i);
	}
}
