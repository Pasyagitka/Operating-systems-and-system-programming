#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	if(fork() == 0)
	{
		system("./5_1");
		exit(0);
	}
	pid_t pid = getpid();
	for (int i = 1; i<100; i++)
	{
		sleep(1);
		printf("os03-06 : %d-%d\n", pid, i);
	}
	exit(0);
}
