#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

#define for_each_addrinfo(p, res) \
	for (p = res; p != NULL; p = p->ai_next)

/* #define URL "www.shoes.com" */
#define URL "www.nastygal.com"
#define PORT "80"

static inline void *get_addr_in(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);
	else
		return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void)
{
	int ret;
	int sockfd;
	int bytes;
	int len;
	struct addrinfo hints, *res, *p;
	char ipstr[INET6_ADDRSTRLEN];
	char msg[BUFFER_SIZE];
	char buf[BUFFER_SIZE];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(URL, PORT, &hints, &res);
	if (ret != 0) {
		printf("getaddrinfo: %s\n", gai_strerror(ret));
		exit(1);
	}

	for_each_addrinfo(p, res) {
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1) {
			perror("socket");
			continue;
		}

		ret = connect(sockfd, p->ai_addr, p->ai_addrlen);
		if (ret != 0) {
			perror("connect");
			close(sockfd);
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "Can't connect to server\n");
		exit(1);
	}

	inet_ntop(p->ai_family, get_addr_in(p->ai_addr), ipstr, sizeof(ipstr));
	printf("connecting to %s\n\n", ipstr);

	freeaddrinfo(res);

	bytes = 0;
	/* strcpy(msg, "GET / HTTP/1.1\r\nHost: www.shoes.com\r\n\r\n"); */
	strcpy(msg, "GET / HTTP/1.1\r\nHost: www.nastygal.com\r\nConnection: close\r\n\r\n");
	len = strlen(msg);
	while (bytes < len) {
		ret = send(sockfd, msg+bytes, len-bytes, 0);
		if (ret < 0) {
			perror("send");
			exit(1);
		}
		bytes += ret;
	}

	while (1) {
		ret = recv(sockfd, buf, BUFFER_SIZE, 0);
		if (ret < 0) {
			perror("recv");
			exit(1);
		} else if (ret == 0) {
			break;
		}
		buf[ret] = '\0';
		printf("%s", buf);
	}


	close(sockfd);

	return 0;
}
