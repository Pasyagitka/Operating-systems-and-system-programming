#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid = getpid();
	for (int i = 1; i<50; i++)
	{
		sleep(1);
		printf("os03_05_1: %d-%d\n",pid, i);
	}
	exit(0);
}
