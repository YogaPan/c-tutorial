#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int read_fd;
	int retval;

	read_fd = open("fcntl.c", O_RDONLY);
	retval = fcntl(read_fd, F_GETFL, 0);

	if (retval < 0) {
		perror("fcntl");
		return 0;
	}

	switch(retval & O_ACCMODE) {
	case O_RDONLY:
		printf("Read only\n");
		break;
	case O_WRONLY:
		printf("write only\n");
		break;
	default:
		break;
	}

	close(read_fd);

	return 0;
}
