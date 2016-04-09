#ifndef __REQUESTS_H__
#define __REQUESTS_H__

#include <netdb.h>

struct host {
	const char *url;
	const char *port;
	char protocol[10];
	char site[32];
	char path[64];
	char ip[INET6_ADDRSTRLEN];
	int sockfd;
};

struct requests_operations {
	struct host *(*init)(const char *url);
	void (*get)(struct host *self);
	void (*destroy)(struct host *self);
} Requests;

#endif /*  __REQUESTS_H__ */
