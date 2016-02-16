#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "sds.h"
#include "testhelp.h"

sds sdsnewlen(const void *init, size_t initlen)
{
        struct sdshdr *sh;

        if (init)
                sh = malloc(sizeof(struct sdshdr)+initlen+1);
        else
                sh = calloc(1, sizeof(struct sdshdr)+initlen+1);

        if (sh == NULL)
                return NULL;

        sh->len = initlen;
        sh->free = 0;
        if (initlen && init)
                memcpy(sh->buf, init, initlen);
        sh->buf[initlen] = '\0';

        return sh->buf;
}

sds sdsempty(void)
{
        return sdsnewlen("", 0);
}

sds sdsnew(const void *init)
{
        size_t initlen = (init == NULL) ? 0 : strlen(init);
        return sdsnewlen(init, initlen);
}

sds sdsdup(const sds s)
{
        return sdsnewlen(s, sdslen(s));
}

void sdsfree(const sds s)
{
        if (s == NULL)
                return;
        free(s-sizeof(struct sdshdr));
}

void sdsclear(sds s)
{
        struct sdshdr *sh = (void *)(s-sizeof(struct sdshdr));
        sh->free += sh->len;
        sh->len = 0;
        sh->buf[0] = '\0';
}

sds sdsMakeRoomFor(sds s, size_t addlen)
{
        struct sdshdr *sh, *newsh;
        size_t free = sdsavail(s);
        size_t len, newlen;

        if (free >= addlen)
                return s;

        len = sdslen(s);
        sh = (void *)(s-sizeof(struct sdshdr));

        newlen = len + addlen;

        if (newlen < SDS_MAX_PREALLOC)
                newlen *= 2;
        else
                newlen += SDS_MAX_PREALLOC;

        newsh = realloc(sh, sizeof(struct sdshdr)+newlen+1);
        if (newsh == NULL)
                return NULL;

        newsh->free = newlen - len;
        return newsh->buf;
}

sds sdsRemoveFreespace(sds s)
{
        struct sdshdr *sh;

        sh = (void *)(s-sizeof(struct sdshdr));
        sh = realloc(sh, sizeof(struct sdshdr)+sh->len+1);
        sh->free = 0;

        return sh->buf;
}

size_t sdsAllocSize(sds s)
{
        struct sdshdr *sh = (void *)(s-(sizeof(struct sdshdr)));
        return sizeof(*sh)+sh->len+sh->free+1;
}

void sdsIncrLen(sds s, int incr)
{
        struct sdshdr *sh = (void *)(s-(sizeof(struct sdshdr)));

        assert(sh->free >= incr);

        sh->len += incr;
        sh->free -= incr;
        s[sh->len] = '\0';
}

sds sdsgrowzero(sds s, size_t len)
{
        struct sdshdr *sh = (void *)(s-(sizeof(struct sdshdr)));
        size_t totlen, curlen = sh->len;

        if (len <= curlen)
                return s;

        s = sdsMakeRoomFor(s, len-curlen);
        if (s == NULL)
                return NULL;

        memset(s+curlen, 0, len-curlen+1);

        totlen = sh->len+sh->free;
        sh->len = len;
        sh->free = totlen-sh->len;

        return s;
}

sds sdscatlen(sds s, const void *t, size_t len)
{
        struct sdshdr *sh = (void *)(s-(sizeof(struct sdshdr)));
        size_t curlen = sdslen(s);

        s = sdsMakeRoomFor(s, len);
        if (s == NULL)
                return NULL;

        memcpy(s+curlen, t, len);
        sh->len = curlen + len;
        sh->free = sh->free - len;
        s[curlen+len] = '\0';

        return s;
}

sds sdscat(sds s, const char *t)
{
        return sdscatlen(s, t, strlen(t));
}

sds sdscatsds(sds s, const sds t)
{
        return sdscatlen(s, t, sdslen(t));
}

sds sdscpylen(sds s, const char *t, size_t len)
{
        struct sdshdr *sh = (void *)(s-(sizeof(struct sdshdr)));
        size_t totlen = sh->free + sh->len;

        if (totlen < len) {
                s = sdsMakeRoomFor(s, len-sh->len);
                if (s == NULL)
                        return NULL;
                sh = (void *)(s-(sizeof(struct sdshdr)));
                totlen = sh->free + sh->len;
        }
        memcpy(s, t, len);
        s[len] = '\0';
        sh->len = len;
        sh->free = totlen - len;

        return s;
}

sds sdscpy(sds s, const char *t)
{
        return sdscpylen(s, t, strlen(t));
}

sds sdstrim(sds s, const char *cset)
{
        struct sdshdr *sh = (void *)(s-(sizeof(struct sdshdr)));
        char *start, *end, *sp, *ep;
        size_t len;

        sp = start = s;
        ep = end = s + sdslen(s) - 1;
        while (sp <= end && strchr(cset, *sp))
                sp++;
        while (ep >start && strchr(cset, *ep))
                ep--;

        len = (sp > ep) ? 0 : ((ep-sp) + 1);

        if (sh->buf != sp)
                memmove(sh->buf, sp, len);

        sh->buf[len] = '\0';
        sh->len = len;
        sh->free = sh->free + (sh->len-len);
        return s;
}

void sdsrange(sds s, int start, int end)
{
        struct sdshdr *sh = (void *)(s-(sizeof(struct sdshdr)));
        size_t newlen, len = sdslen(s);

        if (len == 0)
                return;
        if (start < 0) {
                start = len + start;
                if (start < 0)
                        start = 0;
        }
        if (end < 0) {
                end = len + end;
                if (end < 0)
                        end = 0;
        }

        newlen = (start > end) ? 0 : (end-start) + 1;
        if (newlen != 0) {
                if (start >= (signed)len) {
                        newlen = 0;
                } else if (end >= (signed)len) {
                        end = len - 1;
                        newlen = (start > end) ? 0 : (end-start) + 1;
                }
        } else {
                start = 0;
        }

        if (start && newlen)
                memmove(sh->buf, sh->buf+start, newlen);
        sh->buf[newlen] = '\0';
        sh->len = newlen;
}

void sdstolower(sds s)
{
        int len = sdslen(s);

        for (int i = 0; i < len; i++)
                s[i] = tolower(s[i]);
}

void sdstoupper(sds s)
{
        int len = sdslen(s);

        for (int i = 0; i < len; i++)
                s[i] = toupper(s[i]);
}

int sdscmp(const sds s1, const sds s2)
{
        size_t l1, l2, minlen;
        int cmp;

        l1 = sdslen(s1);
        l2 = sdslen(s2);
        minlen = (l1 < l2) ? l1: l2;
        cmp = memcmp(s1, s2, minlen);

        if (cmp == 0)
                return l1 - l2;
        return cmp;
}

int sdsll2str(char *s, long long value)
{
        char *p, aux;
        unsigned long long v;
        size_t l;

        v = (value < 0) ? -value : value;
        p = s;
        do {
                *p++ = '0' + (v%10);
                v /= 10;
        } while (v);

        if (value < 0)
                *p++ = '-';

        l = p - s;
        *p = '\0';
        p--;
        while (s < p) {
                aux = *s;
                *s = *p;
                *p = aux;
                s++; p--;
        }
        return l;
}

sds sdsfromlonglong(long long value)
{
        char buf[SDS_LLSTR_SIZE];
        int len = sdsll2str(buf, value);

        return sdsnewlen(buf, len);
}

sds sdsjoin(char **argv, int argc, char *sep)
{
        sds join = sdsempty();
        for (int i = 0; i < argc; i++) {
                join = sdscat(join, argv[i]);
                if (i != argc-1)
                        join = sdscat(join, sep);
        }
        return join;
}

int main(int argc, char **argv)
{
        sds s;
        s = sdsnew("fuck");
        printf("my length is %d\n", sdslen(s));
        printf("my free is %d\n", sdsavail(s));
        printf("%s\n", s);
        sdsfree(s);
        return 0;
}
