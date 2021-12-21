#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int f, f1;
    char buf[512];
    f = open("OS09_05.txt", O_RDONLY);

    f1 = lseek(f, 0, SEEK_SET);
    read(f, buf, 15);
    printf("Output: %s\n", buf);
    printf("Current position: %ld\n", f1);

    f1 = lseek(f, 10, SEEK_CUR);
    read(f, buf, 15);
    printf("Output: %s\n", buf);
    printf("Current position: %ld\n", f1);

    close(f);
    return 0;
}
