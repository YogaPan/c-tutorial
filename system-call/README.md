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

extern char **environ;

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
execve(const char *filename, char *const argv[], char *const envp[]);

/* Example usage */
execl("bin/ls", "ls", "-l", NULL); /* "ls" is the first argv */
printf("This will not print if exec success.");

/* "p" means you can execute your programs which in $PATH variable */
execlp("ls", "ls", "-l", "-a", NULL);

/* no "l" means you have to provide an array. */

char *argv[] = { "ls", "-l", NULL };
execvp("ls", argv);

/* "e" means pass environment varialble to exec process. */
char * const envp[] = { "AA=11", "BB=22", NULL };
execle("./hello", "hello", NULL, envp);

```

```C
#include <stdio.h>

FILE *
popen(const char *command, const char *mode);

int
pclose(FILE *stream);
```


## Pthread
```C
#include <pthread.h>

int
pthread_create(pthread_t *thread, const pthread_attr_t *attr,
               void *(*start_routine)(void *), void *arg);

void
pthread_exit(void *value_ptr);

int
pthread_join(pthread_t thread, void **value_ptr);

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

## Signal
```C
#include <signal.h>
/* No    Name         Default Action       Description
 * 1     SIGHUP       terminate process    terminal line hangup
 * 2     SIGINT       terminate process    interrupt program
 * 3     SIGQUIT      create core image    quit program
 * 4     SIGILL       create core image    illegal instruction
 * 5     SIGTRAP      create core image    trace trap
 * 6     SIGABRT      create core image    abort program (formerly SIGIOT)
 * 7     SIGEMT       create core image    emulate instruction executed
 * 8     SIGFPE       create core image    floating-point exception
 * 9     SIGKILL      terminate process    kill program
 * 10    SIGBUS       create core image    bus error
 * 11    SIGSEGV      create core image    segmentation violation
 * 12    SIGSYS       create core image    non-existent system call invoked
 * 13    SIGPIPE      terminate process    write on a pipe with no reader
 * 14    SIGALRM      terminate process    real-time timer expired
 * 15    SIGTERM      terminate process    software termination signal
 * 16    SIGURG       discard signal       urgent condition present on socket
 * 17    SIGSTOP      stop process         stop (cannot be caught or ignored)
 * 18    SIGTSTP      stop process         stop signal generated from keyboard
 * 19    SIGCONT      discard signal       continue after stop
 * 20    SIGCHLD      discard signal       child status has changed
 * 21    SIGTTIN      stop process         background read attempted from control terminal
 * 22    SIGTTOU      stop process         background write attempted to control terminal
 * 23    SIGIO        discard signal       I/O is possible on a descriptor (see fcntl(2))
 * 24    SIGXCPU      terminate process    cpu time limit exceeded (see setrlimit(2))
 * 25    SIGXFSZ      terminate process    file size limit exceeded (see setrlimit(2))
 * 26    SIGVTALRM    terminate process    virtual time alarm (see setitimer(2))
 * 27    SIGPROF      terminate process    profiling timer alarm (see setitimer(2))
 * 28    SIGWINCH     discard signal       Window size change
 * 29    SIGINFO      discard signal       status request from keyboard
 * 30    SIGUSR1      terminate process    User defined signal 1
 * 31    SIGUSR2      terminate process    User defined signal 2 */

int
kill(pid_t, pid, int sig);

typedef void (*sig_t) (int);
sig_t
signal(int sig, sig_t func);


/* Usage example */
void intHandler(int sig)
{
        printf("Good Bye.\n");
        exit(EXIT_SUCCESS);
}

signal(SIGINT, intHandler);

struct sigaction {
        void (*sa_handler)(int);
        void (*sa_sigaction)(int, siginfo_t *, void *);
        sigset_t sa_mask;
        int sa_flags;
};

struct siginfo_t {
        int      si_signo;     /* Signal number */
        int      si_errno;     /* An errno value */
        int      si_code;      /* Signal code */
        int      si_trapno;    /* Trap number that caused hardware-generated signal
                                * (unused on most architectures) */
        pid_t    si_pid;       /* Sending process ID */
        uid_t    si_uid;       /* Real user ID of sending process */
        int      si_status;    /* Exit value or signal */
        clock_t  si_utime;     /* User time consumed */
        clock_t  si_stime;     /* System time consumed */
        sigval_t si_value;     /* Signal value */
        int      si_int;       /* POSIX.1b signal */
        void    *si_ptr;       /* POSIX.1b signal */
        int      si_overrun;   /* Timer overrun count; POSIX.1b timers */
        int      si_timerid;   /* Timer ID; POSIX.1b timers */
        void    *si_addr;      /* Memory location which caused fault */
        long     si_band;      /* Band event (was int in glibc 2.3.2 and
                                * earlier) */
        int      si_fd;        /* File descriptor */
        short    si_addr_lsb;  /* Least significant bit of address
                                * (since Linux 2.6.32) */
        void    *si_call_addr; /* Address of system call instruction
                                * (since Linux 3.5) */
        int      si_syscall;   /* Number of attempted system call (since Linux 3.5) */
        unsigned int si_arch;  /* Architecture of attempted system call
                                * (since Linux 3.5) */
}

int
sigemptyset(sigset_t *set);

int
sigaddset(sigset_t *set, int signo);

int
sigaction(int sig, const struct sigaction *act, struct sigaction *oact);

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

## Errno
```C
#include <errno.h>
/* TODO */
```

## How to see system call in your program
```sh
strace ./your-program
```

## Learning Resources
- [簡介 fork, exec*, pipe, dup2](https://www.ptt.cc/bbs/b97902HW/M.1268932130.A.0CF.html)
- [簡介 fork, exec*, dup2, pipe](https://www.ptt.cc/bbs/b97902HW/M.1268953601.A.BA9.html)
- [簡介檔案系統 (File System)](https://www.ptt.cc/bbs/b97902HW/M.1270924592.A.668.html)
- [簡介 link/stat/chdir/opendir](https://www.ptt.cc/bbs/b97902HW/M.1270981044.A.909.html)
- [linux stat函数讲解](http://www.cnblogs.com/hnrainll/archive/2011/05/11/2043361.html)
- [进程生命周期与PCB（进程控制块）](https://github.com/YogaPan/c-tutorial/tree/master/system-call)
- [进程复制fork，孤儿进程，僵尸进程](http://www.cnblogs.com/mickole/p/3186441.html)
- [进程退出exit，_exit区别即atexit函数](http://www.cnblogs.com/mickole/p/3186606.html)
- [exec系列函数（execl,execlp,execle,execv,execvp)使用](http://www.cnblogs.com/mickole/p/3187409.html)
- [守护进程详解及创建，daemon()使用](http://www.cnblogs.com/mickole/p/3188321.html)
