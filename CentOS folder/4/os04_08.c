#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void* os04_08_t1(void* arg)
{
	pid_t pid = getpid();
	for (int i  = 1; i<75; i++)
	{
		if(i==50)
		{
			printf("os04_08_t1 sleep 10");
			sleep(10);	
		}
		printf("os04_08_t1 %d-%d\n", pid, i);
		sleep(1);
	}
	pthread_exit("os04_08_t1 thread");
}

int main()
{
	pthread_t a_thread;
	void* thread_result;
	pid_t pid = getpid();
	int res = pthread_create(&a_thread, NULL, os04_08_t1, NULL);

	for (int i = 1; i<100; i++)
	{
		if(i==30)
		{
			printf("main sleep 15");
			sleep(15);	
		}
		printf("main %d-%d\n", pid, i);
		sleep(1);
	}
	int status = pthread_join(a_thread, (void**)&thread_result);
	exit(0);
}
