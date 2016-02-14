# Standard Library

## String
```C
#include <stdio.h>

int
sprintf(char *str, const char *fmt, ...);

int
snprintf(char *str, size_t size, const char *fmt, ...);

int
sscanf(const char *str, const char *fmt, ...);

```

```C
#include <string.h>

size_t
strlen(const char *str);

char *
strcpy(char *dst, const char *src);
char *
strncpy(char *dst, const char *src, size_t n);  /* Watch out for null terminator. */

char *
strcat(char *s1, const char *s2);
char *
strncat(char *s1, const char *s2, size_t n);

int
strcmp(const char *s1, const char *s2);
int
strncmp(const *s1, const char *s2, size_t n);

char *
strchr(const char *str, int c);
char *
strrchr(const char *str, int c);

char *
strstr(const char *big, const char *little);
char *
strnstr(const char *big, const char *little, size_t n);

/* Returns a pointer to the first occurrence in str1 of any of the characters that are part of str2,
 * or a null pointer if there are no matches. */
char *
strpbrk(const char *s1, const char *s2);

/* Returns the length of the initial portion of str1
 * which consists only of characters that are part of str2. */
size_t
strspn(const char *s1, const char *s2);
/* Example usage */
char strtext[] = "129th";
char cset[] = "1234567890";
int i = strspn (strtext, cset); /* i = 3 */

/* Scans str1 for the first occurrence of any of the characters that are part of str2,
 * returning the number of characters of str1 read before this first occurrence. */
size_t
strcspn(const char *s1, const char *s2);
/* Example usage */
char str[] = "fcba73";
char keys[] = "1234567890";
int i = strcspn (str, keys);  /* i = 5 */

char *
strtok(char *s1, const char *s1);
/* Example usage */
char s[] = "Speech is si1ver, silence is gold.";
for (char *p = strtok(s, " "); p != NULL; p = strtok(NULL, " "))
        puts(p);

```

## Memory
```C
#include <string.h>
/* TODO */
```

```C
#include <stdlib.h>
/* TODO */
```

## Math
```C
#include <math.h>
/* TODO */
```

## Input
```C
#include <stdio.h>
/* TODO */
```

## Output
```C
#include <stdio.h>
/* TODO */
```

## File
```C
#include <stdio.h>
/* TODO */
```

## Learning resource
- [cplusplus.com](http://www.cplusplus.com/reference/)
