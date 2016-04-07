#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include "requests.h"

#define BUFFER_SIZE 1024

#define for_each_addrinfo(p, res) \
	for (p = res; p != NULL; p = p->ai_next)

/* #define URL "www.shoes.com" */
#define URL "www.nastygal.com"
#define PORT "80"

static inline void *get_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);
	else
		return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

static void get_target(const char *url)
{
	const char *host;
	const char *path;

}

static void get_site(const char *url)
{
	char protocol[100];
	char site[100];
	char path[100];

	sscanf(url, "%[^:]:%*2[/]%[^/]%[a-zA-Z0-9._/-]", protocol, site, path);
	printf("protocol=%s site=%s path=%s\n", protocol, site, path);

	return 0;
}

static int get_socket(const char *url, const char *port)
{
	int ret;
	int sockfd;
	char ipstr[INET6_ADDRSTRLEN];
	struct addrinfo hints, *res, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(url, port, &hints, &res);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		return -1;
	}

	for_each_addrinfo(p, res) {
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1)
			continue;

		ret = connect(sockfd, p->ai_addr, p->ai_addrlen);
		if (ret == -1) {
			close(sockfd);
			continue;
		}
		break;
	}

	if (p == NULL)
		return -1;

	inet_ntop(p->ai_family, get_addr(p->ai_addr), ipstr, INET6_ADDRSTRLEN);
	printf("connect to %s\n\n", ipstr);

	freeaddrinfo(res);

	return sockfd;
}

int main(void)
{
	int ret;
	int sockfd;
	int bytes;
	int len;
	char msg[BUFFER_SIZE];
	char buf[BUFFER_SIZE];

	sockfd = get_socket(URL, PORT);
	if (sockfd == -1) {
		fprintf(stderr, "Can't connect to server\n\n");
		exit(1);
	}

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
