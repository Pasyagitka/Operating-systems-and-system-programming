#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    int lines = 0;
    char buf[512];
    int value = (int)*argv[1]; //принимает целочисленное числовое значение

    FILE *fin = fopen("os09_05.txt", "r"), *fout;

    if (value % 2 == 1) fout = fopen("os09_06_1.txt", "w+"); //truncate
    else                fout = fopen("os09_06_2.txt", "w+");
    
    while (fgets(buf, 512, fin) != NULL) { //reads a line from the specified stream and stores it into the string pointed to by str
        lines++;
        if (lines % 2 == value % 2) fputs(buf, fout); //write string
    }
    fclose(fin);
    return 0;
}