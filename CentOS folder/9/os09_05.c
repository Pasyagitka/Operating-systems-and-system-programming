#include <stdio.h>
#include <stdlib.h>

int count(char *filename) {
    char c;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("fopen error %s", filename);
        return 0;
    }
    int count = 0;

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') ++count;

    fclose(fp);
    return count;
}

int main() {
    printf("Count: %d\n", count("OS09_05.txt"));
    return 0;
}