#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;
    char buf[200];
    const char *filename;

    memset(buf, 0, 200);

    if (argc != 2) {
        fprintf(stderr, "usage: read filename\n");
        exit(1);
    }
    filename = argv[1];
    if ((fd = open(filename, O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }
    if (lseek(fd, 10, SEEK_CUR) == -1) {
        perror("lseek");
        exit(1);
    }
    if (read(fd, buf, 200) == -1) {
        perror("read");
        exit(1);
    }
    printf("%s\n", buf);

    return 0;
}
