#include <stdio.h>

typedef struct treeNode {
    int value;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

typedef struct tree {
    treeNode *root;
    int size;
} tree;

tree *treeCreate(void);
void treeInsert(tree *t, int value);
void treeDelete(tree *t, int value);
void treeTravel(tree *t);
void treeRelease(tree *t);

#define treeSize(t) ((t)->size)
