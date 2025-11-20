#include <stdio.h>
#include <stdlib.h>

#define ARGC (2)

int main (int argc, char *argv[])
{
    int charCnt = 0;
    FILE *f;

    if (argc < ARGC) {
        fprintf (stderr, "%s file not given\n", argv[0]);
    }

    f = fopen (argv[1], "r");
    if (f == NULL) {
        perror (argv[1]);
        exit (1);
    }

    while (1) {
        charCnt = fgetc (f);
        if (charCnt == EOF) {
            break;
        }

        if (fputc (charCnt, stdout) == EOF) {
            exit (1);
        }
    }

    fclose (f);

    exit (0);
}