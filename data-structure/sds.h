#include <stdarg.h>
#include <sys/types.h>

#ifndef __SDS_H__
#define __SDS_H__

typedef char *sds;

struct sdshdr {
        int len;
        int free;
        char buf[];
};

#define SDS_LLSTR_SIZE 21
#define SDS_MAX_PREALLOC (1024*1024)

#define sdslen(s) \
        (((struct sdshdr *)((s)-(sizeof(struct sdshdr))))->len)

#define sdsavail(s) \
        (((struct sdshdr *)((s)-(sizeof(struct sdshdr))))->free)

sds sdsnewlen(const void *init, size_t initlen);
sds sdsnew(const void *init);
sds sdsempty(void);
sds sdsdup(const sds s);
void sdsfree(sds s);

sds sdsgrowzero(sds s, size_t len);
sds sdscatlen(sds s, const void *t, size_t len);
sds sdscat(sds s, const char *t);
sds sdscatsds(sds s, const sds t);
sds sdscpylen(sds s, const char *t, size_t len);
sds sdscpy(sds s, const char *t);

sds sdstrim(sds s, const char *cset);
void sdsrange(sds s, int start, int end);
void sdsupdatelen(sds s);
void sdsclear(sds s);
void sdstolower(sds s);
void sdstoupper(sds s);
int sdscmp(const sds s1, const sds s2);
sds sdsfromlonglong(long long value);
sds sdsjoin(char **argv, int argc, char *sep);

/* Low level functions. */
void sdsclear(sds s);
sds sdsMakeRoomFor(sds s, size_t addlen);
sds sdsRemoveFreespace(sds s);
size_t sdsAllocSize(sds s);
void sdsIncrLen(sds s, int incr);


#endif /* __SDS_H__ */
