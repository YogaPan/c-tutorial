#ifndef __REQUESTS_H__
#define __REQUESTS_H__

struct host {
	char *name;
	char *ip;
	char *port;
	int sockfd;
};

struct requests_operations {
	void (*get)(const char *url);
	void (*post)(const char *url);
} requests;

#endif /* end of include guard: __REQUESTS_H__ */
