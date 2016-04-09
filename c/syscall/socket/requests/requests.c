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

static inline void *get_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in *)sa)->sin_addr);
	else
		return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

static void host_set_url(struct host *self, const char *url)
{
	self->url = url;

	strcpy(self->path, "/");
	sscanf(self->url, "%[^:]:%*2[/]%[^/]/%[a-zA-Z0-9._/-]", self->protocol,
			self->site, self->path);
	/* printf("protocol=%s site=%s path=%s\n", self->protocol, self->site, self->path); */

	if (strcmp(self->protocol, "http") == 0)
		self->port = "80";
	else if (strcmp(self->protocol, "https") == 0)
		self->port = "443";
	else
		fprintf(stderr, "Fatal Error!!\n");
}

static void host_destroy(struct host *self)
{
	close(self->sockfd);
	free(self);
}

static struct host *host_init(const char *url)
{
	int ret;
	struct addrinfo hints, *res, *p;
	struct host *self;

	self = malloc(sizeof(*self));
	if (self == NULL)
		return NULL;

	host_set_url(self, url);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(self->site, self->port, &hints, &res);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		return NULL;
	}

	for_each_addrinfo(p, res) {
		self->sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (self->sockfd == -1)
			continue;

		ret = connect(self->sockfd, p->ai_addr, p->ai_addrlen);
		if (ret == -1) {
			close(self->sockfd);
			continue;
		}
		break;
	}

	if (p == NULL) {
		host_destroy(self);
		return NULL;
	}

	inet_ntop(p->ai_family, get_addr(p->ai_addr), self->ip, INET6_ADDRSTRLEN);
	printf("connect to %s\n\n", self->ip);

	freeaddrinfo(res);

	return self;
}

static void host_get(struct host *self)
{
	int ret;
	int bytes;
	int len;
	char msg[BUFFER_SIZE];
	/* char buf[BUFFER_SIZE]; */
	wchar_t buf[BUFFER_SIZE];

	bytes = 0;
	snprintf(msg, BUFFER_SIZE, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", self->site);
	len = strlen(msg);
	while (bytes < len) {
		ret = send(self->sockfd, msg+bytes, len-bytes, 0);
		if (ret < 0) {
			perror("send");
			exit(1);
		}
		bytes += ret;
	}

	while (1) {
		ret = recv(self->sockfd, buf, BUFFER_SIZE-1, 0);
		if (ret < 0) {
			perror("recv");
			exit(1);
		} else if (ret == 0) {
			break;
		}
		/* buf[ret] = '\0'; */
		/* printf("%s", buf); */
		write(1, buf, ret);
	}
}

struct requests_operations Requests = {
	.init    = host_init,
	.get     = host_get,
	.destroy = host_destroy,
};
