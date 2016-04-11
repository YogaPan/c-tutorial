# Unix System Call

## Open file
```C
#include <fctnl.h>

int
open(const char *path, int flag, mode_t mode);

/* creat(path, mode) is the same as open(path, O_CREAT | O_TRUNC | O_WRONLY, mode) */
int
creat(const char *path, mode_t mode);

/* flag options */
O_RDONLY    /* Read only */
O_WRONLY    /* Write only */
O_RDWR      /* Read and Write */

O_CREAT     /* If not exists, then create file */
O_APPEND    /* Append */
O_TRUNC     /* If file existed, then replace this file. */

/* mode macros */
S_ISUID     /* 04000 */
S_ISGID     /* 02000 */
S_ISVTX     /* 01000 sticky */

S_IRWXU     /* 00700 */
    S_IRUSR /* 00400 */
    S_IWUSR /* 00200 */
    S_IXUSR /* 00100 */

S_IRWXG     /* 00070 */
    S_IRGRP /* 00040 */
    S_IWGRP /* 00020 */
    S_IXGRP /* 00010 */

S_IRWXO     /* 00007 */
    S_IROTH /* 00004 */
    S_IWOTH /* 00002 */
    S_IXOTH /* 00001 */

/* Usage example */
fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
fd = creat(filename, 0755);
```

## Read, write, redirect and close file
```C
#include <unistd.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

ssize_t
read(int fildes, void *buf, size_t nbyte);

ssize_t
write(int fildes, const void *buf, size_t nbyte);

off_t
lseek(int fildes, off_t offset, int whence);
/* whence */
SEEK_SET  /* If whence is SEEK_SET, the offset is set to offset bytes. */
SEEK_CUR  /* If whence is SEEK_CUR, the offset is set to its current location plus offset bytes. */
SEEK_END  /* If whence is SEEK_END, the offset is set to the size of the file plus offset bytes. */

int
dup(int fildes);

int
dup2(int fildes, int fildes2);

int
pipe(int pipefd[2]);

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

/* Usage example */
cwd_fd = open('.', O_RDONLY);
chdir("the other directory");
fchdir(cwd_fd);
close(cwd_fd);

```

```C
#include <sys/stat.h>

int
mkdir(const char *pathname, mode_t mode);
```

```C
#include <dirent.h>

struct dirent {
        ino_t d_ino;
        char d_name[255+1];
}

DIR *
opendir(const char *filename);

struct dirent *
readdir(DIR *dirp);

int
closedir(DIR *dirp);

/* Usage example */
DIR *dir = opendir('path');
if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
                printf("%s\n", entry->d_name);
        closedir(dir);
}

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
#include <sys/stat.h>

struct stat {
        dev_t st_dev;
        ino_t st_ino;           /* inode number */
        mode_t st_mode;         /* mode */
        nlinkt st_nlink;        /* how many link */
        uid_t st_uid;           /* uid */
        git_t st_gid;           /* gid */
        dev_t st_rdev;
        off_t st_size;          /* file size */
        time_t st_atime;        /* last access time */
        time_t st_mtime;        /* last modify time */
        time_t st_ctime;
        blksize_t st_blksize;   /* recommend block size */
        blkcnt_t st_blocks;
};

S_ISREG(st_mode);   /* Regular File */
S_ISDIR(st_mode);   /* Directory */
S_ISLNK(st_mode);   /* Symbolic Link */
S_ISSOCK(st_mode);  /* Socket */
S_ISBLK(st_mode);   /* Block Special Device */
S_ISCHR(st_mode);   /* Character Special Device */
S_ISFIFO(st_mode);  /* FIFO */

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

```C
#include <stdio.h>

FILE *
popen(const char *command, const char *mode);

int
pclose(FILE *stream);
```

## Exit
```C
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/* Before termination, exit() performs the following functions in the order listed:
 * 1. Call the functions registered with the atexit(3) function,
 *    in the reverse order of their registration.
 * 2. Flush all open output streams.
 * 3. Close all open streams.
 * 4. Unlink all files created with the tmpfile(3) function */
void
exit(int status);

int
atexit(void (*func)(void));

```

```C
#include <unistd.h>

/* 1. Any open file descriptors belonging to the process are closed.
 * 2. Any children of the process are inherited  by process 1, init.
 * 3. the process's parent is sent a SIGCHLD signal */
void
_exit(int status);

```
## Time
```C
#include <sys/time.h>

#define ITIMER_REAL      0            /* SIGALRM */
#define ITIMER_VIRTUAL   1            /* SIGTALRM */
#define ITIMER_PROF      2            /* SIGPROF */

struct itimerval {
        struct timeval it_interval;   /* timer interval */
        struct timeval it_value;      /* current value */
};

struct timeval {
        time_t tv_sec;                /* seconds */
        suseconds_t tv_usec;          /* microseconds */
};

int
getitimer(int which, struct itimerval *value);

int
setitimer(int which, const struct itimerval value, struct timeval ovalue);

```

## How to see system call in your program
```sh
$ strace ./your-program
```

## Learning Resources
- [簡介檔案系統 (File System)](https://www.ptt.cc/bbs/b97902HW/M.1270924592.A.668.html)
- [簡介 link/stat/chdir/opendir](https://www.ptt.cc/bbs/b97902HW/M.1270981044.A.909.html)
- [linux stat函数讲解](http://www.cnblogs.com/hnrainll/archive/2011/05/11/2043361.html)
- [进程退出exit，_exit区别即atexit函数](http://www.cnblogs.com/mickole/p/3186606.html)
