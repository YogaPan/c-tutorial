#ifndef __REQUESTS_H__
#define __REQUESTS_H__

struct host {
	const char *url;
	const char *port;
	char protocol[10];
	char site[32];
	char path[64];
	char ip[INET6_ADDRSTRLEN];
	int sockfd;
};

#endif /*  __REQUESTS_H__ */
