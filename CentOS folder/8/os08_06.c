#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

//должно выполнять замер реального затраченного на работу цикла времени  и выводить его значения на консоль
int main() {
	struct timespec start, end, proc;
	clock_gettime(CLOCK_REALTIME, &start);
	int i = 0;
	for(;;) {
		i++;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);
		if(proc.tv_sec == 2) break;
		//Выведите на консоль значения счетчика итераций через 2 сек. процессорного времени и корректно завершите цикл.
	}
	clock_gettime(CLOCK_REALTIME, &end);	
	printf("After 2 sec: %d\n", i);
	printf("Real time: %ld s %ld ns\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
	exit(0);
}