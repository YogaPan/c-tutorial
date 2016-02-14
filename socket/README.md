# C Socket practice

## Data structure
```C
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

struct addrinfo {
        int ai_flags;               /* AI_PASSIVE, AI_CANONNAME */
        int ai_family;              /* AF_INET, AF_INET6, AF_UNSPEC */
        int ai_socktype;            /* SOCK_STREAM, SOCK_DGRAM */
        int ai_protocol;            /* "0" means any. */
        size_t ai_addrlen;          /* sizeof ai_addr */
        struct sockaddr *ai_addr;   /* struct sockaddr_in or sockaddr_in6 */
        char *ai_cannonname;        /* hostname */
        struct addrinfo *ai_next;   /* next node */
};

struct sockaddr {
        unsigned short sa_famaly;   /* AF_XXX */
        char sa_data[14];           /* 14 bytes of protocol address */
};

struct sockaddr_in {
        short int sin_family;        /* address family, AF_XXX */
        unsigned short int sin_port; /* port number */
        struct in_addr sin_addr;     /* Internet address */
        unsigned char sin_zero[8];   /* same as struct sockaddr size */
};

struct in_addr {
        uint32_t s_addr;             /* That's 32-bit int (4 bytes) */
};

int getaddrinfo(const char *node,
                const char *service
                const struct addrinfo *hint
                const addrinfo **res);

const char *inet_ntop(int af, const char *src, void *dst);

```

## Basic server
```C
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

int status;
struct addrinfo hints;
struct addrinfo *servinfo;

memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE;

if ((status = getaddrinfo(NULL, "3000", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
}

/*
 * Do whatever you want.
 */

freeaddrinfo(servinfo);

```

## Basic client
```C
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int status;
char ipstr[INET6_ADDRSTRLEN];
struct addrinfo hints, *res, *p;

memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

if ((status = getaddrinfo("www.google.com", NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
}

for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        if (p->ai_family == AF_INET) {
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
                addr = &(ipv4->sin_addr);
                ipver = "IPv4";
        } else {
                struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
                addr = &(ipv6->sin6_addr);
                ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf(" %s: %s\n", ipver, ipstr);
}

freeaddrinfo(res);

```

## Socket
```C

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int socket(int domain, int type, int protocol);

int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);

int send(int sockfd, const void *msg, int len, int flags);
int recv(int sockfd, void *msg, int len, int flags);

/* Usage example */
sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

bind(sockfd, res->ai_addr, res->ai_addrlen);
listen(sockfd, 20);
client_sock = accept(sockfd, (struct sockaddr *)&client_addr, &sizeof(addr_size));

/* You better check bytes_sent equal to strlen. */
bytes_sent = send(sockfd, msg, strlen(msg), 0);
recv(sockfd, *msg, 1024, 0);

connect(sockfd, res->ai_addr, res->ai_addrlen);

int shutdown(int sockfd, int how);
/*
 * 0 不允許再接收資料
 * 1 不允許再傳送資料
 * 2 不允許再傳送與接收資料
 */
int close(sockfd);
```

## Create server workflow
```C

getaddrinfo();
socket();
bind();
listen();
accept();

```

## Make sure your port can use
```C
int yes = 1; /* solaris user: char yes = "1"; */
if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
}
```

## Learning Resources
- [Beej's Guide to Network Programming 正體中文版](http://beej-zhtw-gitbook.netdpi.net/WhatIsSocket.html)
- [tinyhttp](https://github.com/cbsheng/tinyhttpd)
