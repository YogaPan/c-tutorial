#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, const char **argv)
{
        struct stat s;
        const char *filename;
        if (argc != 2) {
                fprintf(stderr, "usage: stat filename\n");
                exit(1);
        }

        filename = argv[1];
        if (stat(filename, &s) == -1) {
                perror("stat");
                exit(1);
        }

        if (S_ISDIR(s.st_mode))
                printf("%s is a directory\n", filename);
        else
                printf("%s is a file\n", filename);
        printf("%lld\n", s.st_size);
        printf("%o\n", s.st_mode);
        printf("%ld\n", s.st_ctime);

        return 0;
}
