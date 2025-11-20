#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define STD_IN
#ifdef STD_IN
    #define ARGC (1)
#else
    #define ARGC (2)
#endif
#define BUFFER_SIZE (128)

int main (int argc, char *argv[])
{
    int fd;
    unsigned char buf [BUFFER_SIZE];
    ssize_t size;

    if (argc < ARGC) {
        fprintf (stderr, "%s file not given\n", argv[0]);
    }

#ifdef STD_IN
    // --- 標準入力から読み込む
    size = read (STDIN_FILENO, buf, BUFFER_SIZE);
    if (size < 0) {
        printf ("read err\n");
        perror (argv[1]);
        exit (1);
    }
#else // STD_IN
    // --- ファイルオープン
    fd = open (argv[1], O_RDONLY);  // path(argv[1]のFDを開く)
    if (fd < 0) {
        perror (argv[1]);
        exit (1);
    }

    // --- FDから読み込む
    size = read (fd, buf, BUFFER_SIZE);
    if (size < 0) {
        printf ("read err\n");
        perror (argv[1]);
        exit (1);
    }
#endif // STD_IN

    // --- 標準出力へ書き出す
    if (0 > (write (STDOUT_FILENO, buf, size))) {
        printf ("write err\n");
        perror (argv[1]);
        exit (1);
    }

    // --- FDを閉じる
   if (0 > (close (fd))) {
        perror (argv[1]);
        exit (1);
   }

    exit (0);
}