# ASM

## int 0x80

syscall | Param1 | Param2 | Param3 | Param4 | Param5
--------|--------|--------|--------|--------|-------
eax     | ebx    | ecx    | edx    | esi    | edi

| return |
|--------|
| eax    |

## syscall

syscall | Param1 | Param2 | Param3 | Param4 | Param5
--------|--------|--------|--------|--------|-------
rax     | rdi    | rsi    | r10    | r8     | r9

| return |
|--------|
| rax    |

## Hello Example

### Function Prototypes
```C
ssize_t
write(int fd, const void *buf, size_t count);

void
_exit(int status);
```

### arch/x86/include/asm/unistd_64.h
```C
#define __NR_write 1
#define __NR_exit 60
```

### Use C
```C
include <unistd.h>

int main(void)
{
        write(1, "Hello World\n", 12);
        _exit(0);
}
```

### Use ASM
```asm
.date
msg: .ascii "Hello World\n"

.text
.global _start

_start:
    movq    $1, %rax
    movq    $1, %rdi
    movq    $msg, %rsi
    movq    $12, %rdx
    syscall

    movq    $60, %rax
    movq    $0, %rdi
    syscall
```

## Link
[X86 Assembly/Interfacing with Linux](https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux)
