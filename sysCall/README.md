# Unix System Call

## Open file
```C
#include <fctnl.h>

int
open(const char *path, int oflag, ...);

O_RDONLY
O_WRONLY
O_RDWR

O_CREAT
O_APPEND
O_TRUNC

/* Usage example */
fd = open(filename, O_WRONLY, O_CREAT, O_TRUNC, 0755);
```

## Close file
```C
#include <unistd.h>

int
close(int fildes);

```

## Read file
```C
#include <unistd.h>

ssize_t
read(int fildes, void *buf, size_t nbyte);
```

## Write file
```C
#include <unistd.h>

ssize_t
write(int fildes, const void *buf, size_t nbyte);
```
