#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("os03-07: Start parent process\n");
	if (fork() == 0) 
	{
		execv("./5_1", NULL);
		exit(0);
	}

	for (int i = 1; i<100; i++)
	{
		sleep(1);
		printf("os03-07 : %d-%d\n", getpid(), i);
	}
	printf("os03-07: Finish parent process\n");
	exit(0);
}
