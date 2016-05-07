#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fctnl.h>

#define BUFFER_SIZE 1024

static int copy_file(const char *from, const char *to)
{
	int ret;
	int bytes;
	int read_fd, write_fd;
	char buf[BUFFER_SIZE];

	read_fd = open(from, O_RDONLY);
	if (read_fd == -1) {
		perror("open");
		return -1;
	}
	write_fd = creat(to, 0755);
	if (write_fd == -1) {
		perror("creat");
		close(read_fd);
		return -1;
	}

	for (;;) {
		ret = read(read_fd, buf, BUFFER_SIZE);
		if (ret == -1) {
			perror("read");
			close(read_fd);
			close(write_fd);
			return -1;
		} else if (ret == 0) {
			break;
		}

		bytes = ret;

		ret = write(write_fd, buf, bytes);
		if (ret == -1) {
			perror("write");
			close(read_fd);
			close(write_fd);
			return -1;
		}
	}

	close(read_fd);
	close(write_fd);

	return 0;
}

int main(int argc, const char *argv[])
{
	const char *from = argv[1];
	const char *to   = argv[2];

	return 0;
}
