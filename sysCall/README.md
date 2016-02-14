# Unix System Call

## Open file
```C
#include <fctnl.h>

int
open(const char *path, int oflag, ...);

/* oflag options */
O_RDONLY  /* Read only */
O_WRONLY  /* Write only */
O_RDWR    /* Read and Write */

O_CREAT   /* If not exists, then create file */
O_APPEND  /* Append */
O_TRUNC   /* If file existed, then replace this file. */

/* Usage example */
fd = open(filename, O_WRONLY, O_CREAT, O_TRUNC, 0755);
```

## Read, write, redirect and close file.
```C
#include <unistd.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

ssize_t
read(int fildes, void *buf, size_t nbyte);

ssize_t
write(int fildes, const void *buf, size_t nbyte);

int
dup(int fildes);

int
dup2(int fildes, int fildes2);

int
close(int fildes);

```

## Directory
```C
#include <unistd.h>

char *
getcwd(char *buf, size_t size);

int
rmdir(const char *pathname);

int
chdir(const char *path);

int
fchdir(int fildes);

#include <sys/stat.h>

int
mkdir(const char *pathname, mode_t mode);

```

## Link
```C
#include <unistd.h>

int
link(const char *path1, const char *path2);

int
symlink(const char *path1, const char *path2);

int
unlink(const char *path);

```

## File stat
```C
int
stat(const char *path, struct stat *buf);

int
lstat(const char *path, struct stat *buf);

int
fstat(int fildes, struct stat *buf);

int
chmod(const char *path, mode_t mode);

int
fchmod(int fildes, mode_t mode_t);

```

## Proccess
```C
#include <unistd.h>

pid_t
getpid(void);

uid_t
getuid(void);

gid_t
getgid(void);

pid_t
fork(void);

/* Usage example */
pid_t proc = fork()
if (proc < 0) {
        /* Failed to create child process. */
} else if (proc == 0) {
        /* In the child process. */
} else {
        /* In the parant process. */
        /* proc = child pid */
}

int
execl(const char *path, const char *arg0, ... /*, (char *)0 */);

unsigned int
sleep(unsigned int second);

```

## Learning Resources
- [簡介 fork, exec*, pipe, dup2](https://www.ptt.cc/bbs/b97902HW/M.1268932130.A.0CF.html)
- [簡介 fork, exec*, dup2, pipe](https://www.ptt.cc/bbs/b97902HW/M.1268953601.A.BA9.html)
