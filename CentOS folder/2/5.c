#include <stdio.h>
#include <unistd.h>

int main(void) {
	for (int i = 0; i<1000; i++) {
	printf("Message number: %d, PID: %d\n", i, getpid());
	sleep(2);	
	}	
	return 0;
}
