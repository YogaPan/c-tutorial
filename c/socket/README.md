# C Socket practice

## Socket
```C

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

bind(sockfd, res->ai_addr, res->ai_addrlen);
listen(sockfd, 20);
client_sock = accept(sockfd, (struct sockaddr *)&client_addr, &sizeof(addr_size));

int shutdown(int sockfd, int how);
/*
 * 0 不允許再接收資料
 * 1 不允許再傳送資料
 * 2 不允許再傳送與接收資料
 */
```

## Create server workflow
getaddrinfo() -> socket() -> bind() -> listen() -> accept() -> close

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
