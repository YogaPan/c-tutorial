#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

int main(void)
{
	int epfd;

	epfd = epoll_create(32);
	if (epfd < 0) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	close(epfd);

	return 0;
}
