#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("%d\n", getpid());
	int size = 256 * 1024 * 1024;

	int *block;
	block = malloc(size);
	printf("Address: %p\n", block);

	for(int i=0; i < size/4; i++)
	{
		block[i] = i;
	}
    sleep(60*60*60);
}
