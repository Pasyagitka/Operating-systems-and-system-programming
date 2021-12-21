#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void* os04_07_t1(void* arg)
{
	pid_t pid = getpid();
	for (int i  = 1; i<75; i++)
	{
		sleep(1);
		printf("os04_07_t1 %d-%d\n", pid, i);
	}
	pthread_exit("os04_07_t1 thread");
}

int main()
{
	pthread_t a_thread;
	void* thread_result;
	pid_t pid = getpid();
	int res = pthread_create(&a_thread, NULL, os04_07_t1, NULL);

	for (int i = 1; i<100; i++)
	{
		sleep(1);
		printf("main %d-%d\n", pid, i);
	}
	int status = pthread_join(a_thread, (void**)&thread_result);
	exit(0);
}
