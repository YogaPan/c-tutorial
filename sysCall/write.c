#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        int fd;
        char *filename = argv[1];
        char *message = argv[2];
        if (argc != 3) {
                fprintf(stderr, "usage: write filename content\n");
                exit(1);
        }
        if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1) {
                perror("creat");
                exit(1);
        }
        if (write(fd, message, strlen(message)) == -1) {
                perror("write");
                exit(1);
        }
        close(fd);
        return 0;
}
