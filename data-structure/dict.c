#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "dict.h"

static int dict_can_resize = 1;
static unsigned int dict_force_resize_ratio = 5;

static void _dictReset(dictht *ht)
{
	ht->table = NULL;
	ht->size = 0;
	ht->sizemask = 0;
	ht->used = 0;
}

int _dictInit(dict *d, dictType *type, void *privDataPtr)
{
	_dictReset(&d->ht[0]);
	_dictReset(&d->ht[1]);

	d->type = type;
	d->privdata = privDataPtr;
	d->iterators = 0;
	return DICT_OK;
}

dict *dictCreate(dictType *type, void *privDatePtr)
{
	dict *d = malloc(sizeof(*d));

	_dictInit(d, type, privDatePtr);

	return d;
}

int dictRehash(dict *d, int n)
{
	if (!dictIsRehashing(d)) return 0;

	while (n--) {
		dictEntry *de, *nextde;
		if (d->ht[0].used == 0) {
			free(d->ht[0].table);
			d->ht[0] = d->ht[1];
			_dictReset(&d->ht[1]);
			d->rehashidx = -1;
			return 0;
		}

		assert(d->ht[0].size > (unsigned)d->rehashidx);
		while (d->ht[0].table[d->rehashidx] == NULL) d->rehashidx++;
		de = d->ht[0].table[d->rehashidx];

		while (de) {
			unsigned int h;
			nextde = de->next;
			h = dictHashKey(d, de->key) & d->ht[1].sizemask;
			de->next = d->ht[1].table[h];
			d->ht[1].table[h] = de;

			d->ht[0].used--;
			d->ht[1].used++;

			de = nextde;
		}
		d->ht[0].table[d->rehashidx] = NULL;
		d->rehashidx++;
	}
	return 1;
}

static unsigned long _dictNextPower(unsigned long size)
{
	unsigned long i = DICT_HT_INITIAL_SIZE;
	if (size >= LONG_MAX)
		return LONG_MAX;
	while (1) {
		if (i >= size)
			return i;
		i *= 2;
	}
}

static void _dictRehashStep(dict *d)
{
	if (d->iterators == 0) dictRehash(d, 1);
}

static int _dictExpandIfNeeded(dict *d)
{
	if (dictIsRehashing(d))
		return DICT_OK;
	if (d->ht[0].size == 0)
		return dictExpand(d, DICT_HT_INITIAL_SIZE);
	if (d->ht[0].used >= d->ht[0].size &&
			(dict_can_resize ||
			 d->ht[0].used / d->ht[0].size > dict_force_resize_ratio))
	{
		return dictExpand(d, d->ht[0].used*2);
	}
	return DICT_OK;
}

static int _dictKeyIndex(dict *d, const void *key)
{
	unsigned int h, idx, table;
	dictEntry *he;

	if (_dictExpandIfNeeded(d) == DICT_ERR)
		return -1;
	h = dictHashKey(d, key);
	for (table = 0; table <= 1; table++) {
		idx = h & d->ht[table].sizemask;
		he = d->ht[table].table[idx];
		while (he) {
			if (dictCompareKeys(d, key, he->key))
				return -1;
			he = he->next;
		}
		if (!dictIsRehashing(d))
			break;
	}
	return idx;
}

int dictExpand(dict *d, unsigned long size)
{
	dictht n;
	unsigned long realsize = _dictNextPower(size);

	if (dictIsRehashing(d) || d->ht[0].used > size)
		return DICT_ERR;

	n.size = realsize;
	n.sizemask = realsize - 1;
	n.table = calloc(realsize, sizeof(dictEntry *));
	n.used = 0;

	if (d->ht[0].table == NULL) {
		d->ht[0] = n;
	} else {
		d->ht[1] = n;
		d->rehashidx = 0;
	}
	return DICT_OK;
}

dictEntry *dictAddRaw(dict *d, void *key)
{
	int index;
	dictEntry *entry;
	dictht *ht;

	if (dictIsRehashing(d))
		_dictRehashStep(d);

	if ((index = _dictKeyIndex(d, key)) == -1)
		return NULL;

	ht = dictIsRehashing(d) ? &d->ht[1] : &d->ht[0];
	entry = malloc(sizeof(*entry));
	entry->next = ht->table[index];
	ht->table[index] = entry;
	ht->used++;
	dictSetKey(d, entry, key);

	return entry;
}

int dictAdd(dict *d, void *key, void *val)
{
	dictEntry *entry = dictAddRaw(d, key);
	if (!entry)
		return DICT_ERR;
	dictSetVal(d, entry, val);
	return DICT_OK;
}

int main(int argc, char **argv)
{
	return 0;
}
