#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void cycle(int k, char* s){
	for (int i = 0; i<k; i++) {
		sleep(1);
		printf("%s %d\n", s, i);
	}
}

int main()
{
	pid_t pid;
	switch (pid = fork())
	{
		case -1: perror("fork error"); exit(-1);
		case  0: nice(10); cycle(1000, "child"); exit(0);
		default: cycle(1000, "main");  wait(NULL);
	}
	exit(0);
}
