#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void cycle(char* s, int count)
{
	pid_t pid = getpid();
	for (int i = 1; i<count; i++)
	{
		sleep(1);
		printf("%s: %d-%d\n", s, pid, i);
	}
}

int main()
{
	pid_t pid;
	switch(pid = fork())
	{
	case -1: perror("fork error"); exit(-1);
	case 0: cycle("os03_05_1", 50); exit(0);
	default: cycle("main", 100); wait(NULL);
	}
	exit(0);
}
