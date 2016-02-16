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
        while ((entry = readdir(dir)) != NULL) {
                printf("%s\n", entry->d_name);
        }
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
}

S_ISREG(st_mode)   /* Regular File */
S_ISDIR(st_mode)   /* Directory */
S_ISLNK(st_mode)   /* Symbolic Link */
S_ISSOCK(st_mode)  /* Socket */
S_ISBLK(st_mode)   /* Block Special Device */
S_ISCHR(st_mode)   /* Character Special Device */
S_ISFIFO(st_mode)  /* FIFO */

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

unsigned int
sleep(unsigned int second);

int
execl(const char *path, const char *arg, ...);
int
execlp(const char *file, const char *arg, ...);
int
execle(const char *path, const char *arg, ..., char * const envp[]);
int
execv(const char *path, char *const argv[]);
int
execvp(const char *file, char *const argv[]);
/* Above functions all implement by execve(). */
int
execve(const char *filename, char *const argv[],char *const envp[]);

/* Example usage */
execl("bin/ls", "ls", "-l", NULL); /* "ls" is the first argv */
printf("This will not print if exec success.");

/* "p" means you can execute your programs which in $PATH variable */
execlp("ls", "ls", "-l", "-a", NULL);

/* no "l" means you have to provide a array. */

execl


```

## Pthread
```C
#include <pthread.h>

int
pthread_create(pthread_t *thread, const pthread_attr_t *attr,
               void *(*start_routine)(void *), void *arg);

int
pthread_join(pthread_t thread, void **value_ptr);

```

## Signal
```C
#include <signal.h>
/* TODO */
```


## Time
```C
#include <sys/time.h>
/* TODO */
```

## Errno
```C
#include <errno.h>
/* TODO */
```

## Learning Resources
- [簡介 fork, exec*, pipe, dup2](https://www.ptt.cc/bbs/b97902HW/M.1268932130.A.0CF.html)
- [簡介 fork, exec*, dup2, pipe](https://www.ptt.cc/bbs/b97902HW/M.1268953601.A.BA9.html)
- [簡介檔案系統 (File System)](https://www.ptt.cc/bbs/b97902HW/M.1270924592.A.668.html)
- [簡介 link/stat/chdir/opendir](https://www.ptt.cc/bbs/b97902HW/M.1270981044.A.909.html)
- [linux stat函数讲解](http://www.cnblogs.com/hnrainll/archive/2011/05/11/2043361.html)
