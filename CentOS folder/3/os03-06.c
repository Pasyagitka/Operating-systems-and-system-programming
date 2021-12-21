#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("Start parent process\n");
	printf("5_1 process\n");
	system("./5_1");

	printf("main process\n");
	pid_t pid = getpid();
	for (int i = 1; i<100; i++)
	{
		sleep(1);
		printf("os03-06 : %d-%d\n", pid, i);
	}
	printf("Finish parent process\n");
	exit(0);
}
