#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

tree *treeCreate(void)
{
	tree *t;
	t = (tree *)malloc(sizeof(t));

	t->root = NULL;
	t->size = 0;

	return t;
}

void treeInsert(tree *t, int value)
{
	treeNode *curr, *newNode;

	newNode = (treeNode *)malloc(sizeof(treeNode));
	newNode->value = 0;
	newNode->right = newNode->right = NULL;

	curr = t->root;
	while (curr) {
		if (value > curr->value) {
			if (curr->right)
				curr = curr->right;
			else {
				curr->right = newNode;
				break;
			}
		} else if (value < curr->value) {
			if (curr->left)
				curr = curr->left;
			else {
				curr->left = newNode;
				break;
			}
		}
	}
}

void treeRelease(tree *t)
{
	treeNode *curr;

	curr = t->root;
	while (curr != NULL) {

	}
	free(t);
}

void treeTravel(tree *t)
{
	treeNode *curr;

	curr = t->root;
}

/* This main function used to test and debug. */
int main(void)
{
	return 0;
}
