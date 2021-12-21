#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mx;

void* A(void* arg)
{
	for(int i = 1; i <= 90; i++)
	{
		if (i == 29 || i == 60) pthread_mutex_lock(&mx);
		if (i == 59 || i == 61) pthread_mutex_unlock(&mx);
		usleep(100000);
		printf("child A %d\n", i);
	}
	pthread_exit("Child thread");
}

void* B(void* arg)
{
	for(int i = 1; i <= 90; i++)
	{
		usleep(100000);
		if (i == 29 || i == 60) pthread_mutex_lock(&mx);
		if (i == 59 || i == 61) pthread_mutex_unlock(&mx);
		printf("child B %d\n", i);
	}
	pthread_exit("Child thread");
}

int main()
{
	pthread_mutex_init(&mx, NULL);
	pthread_t th1, th2;
	void *r_th1, *r_th2;
	
	int res1 = pthread_create(&th1, NULL, A, NULL);
	int res2 = pthread_create(&th2, NULL, B, NULL);
	for(int i = 1; i <= 90; i++)
	{
		if (i == 29 || i == 60) pthread_mutex_lock(&mx);
		if (i == 59) pthread_mutex_unlock(&mx);
		printf("main %d\n", i);
		usleep(100000);
	}
	int status1 = pthread_join(th1, (void**)&r_th1);
	int status2 = pthread_join(th2, (void**)&r_th2);
	pthread_mutex_destroy(&mx);
	exit(0);
}
