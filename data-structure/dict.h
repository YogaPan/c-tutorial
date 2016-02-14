#include <stdint.h>

#ifndef __DICT_H__
#define __DICT_H__

typedef struct dictEntry {
    void *key;
    union {
        void *val;
        uint64_t u64;
        uint64_t s64;
    } v;
    struct dictEntry *next;
} dictEntry;

typedef struct dictType {
    unsigned int (*hashFunction)(const void *key);
    void *(*keyDup)(void *privdata, const void *key);
    void *(*valDup)(void *privdata, const void *obj);
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);
    void (*keyDestructor)(void *privdata, const void *key);
    void (*valDestructor)(void *privdata, const void *key);
} dictType;

typedef struct dictht {
    dictEntry **table;
    unsigned long size;
    unsigned long sizemask;
    unsigned long used;
} dictht;

typedef struct dict {
    dictType *type;
    void *privdata;
    dictht ht[2];
    int rehashidx;
    int iterators;
} dict;

typedef struct dictIterator {
    dict *d;
    int table, index, safe;
    dictEntry *entry, nextEntry;
    long long fingerprint;
} dictIterator;

#define DICT_HT_INITIAL_SIZE 4
#define DICT_OK 0
#define DICT_ERR 1
#define DICT_NOTUSED(V) ((void) V)

/* ----------------------- Macros --------------------------*/

#define dictFreeVal(d, entry) \
    if ((d)->type->valDestructor) \
        (d)->type->valDestructor((d)->privdata, (entry)->v.val)

#define dictSetVal(d, entry, _val_) do { \
    if ((d)->type->valDup) \
        entry->v.val = (d)->type->valDup((d)->privdata, _val_); \
    else \
        entry->v.val = (_val_); \
} while (0)

#define dictSetKey(d, entry, _key_) do { \
    if ((d)->type->keyDup) \
        entry->key = (d)->type->keyDup((d)->privdata, _key_); \
    else \
        entry->key = (_key_); \
} while (0)

#define dictSetSignedIntegerVal(entry, _val_) \
    do { entry->v.s64 = _val_ ;} while (0)

#define dictCompareKeys(d, key1, key2) \
    (((d)->type->keyCompare) ? \
        (d)->type->keyCompare((d)->privdata, key1, key2) : \
        (key1) == (key2))

#define dictHashKey(d, key) (d)->type->hashFunction(key)
#define dictIsRehashing(ht) ((ht)->rehashidx != -1)

dict *dictCreate(dictType *type, void *privDataPtr);
void *dictRelease(dict *d);
int dictExpand(dict *d, unsigned long size);
int dictRehash(dict *d, int n);
int dictAdd(dict *d, void *key, void *val);
dictEntry *dictAddRaw(dict *d, void *key);


#endif /* __DICT_H__ */
