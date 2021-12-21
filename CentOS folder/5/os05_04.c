#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>

#define gettid() ((pid_t)syscall(SYS_gettid))

int main() {
	cpu_set_t set;
	CPU_ZERO(&set); //Clears set, so that it contains no CPUs.
	printf("PID: %d\n", getpid());
	printf("TID: %d\n", gettid());
	printf("Current thread priority: %d\n", getpriority(PRIO_PROCESS, 0));
	if(sched_getaffinity(0, sizeof(cpu_set_t), &set) == 0) { //pid, cpusetsize, *mask
		for (int i = 0; i < CPU_SETSIZE; i++)
			printf("CPU = %i is %s\n", i, CPU_ISSET(i, &set) ?"set":"unset");
	}
	else printf("sched_getaffinity ERROR");
	return 0;
}