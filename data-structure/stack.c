#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/* Create a new stack and return address.
 * if false, return NULL. */
stack *stackCreate(void)
{
        stack *s;

        s = malloc(sizeof(stack));
        if (s == NULL)
                return NULL;
        s->len = 0;
        s->top = NULL;
        s->dup = NULL;
        s->free = NULL;
        s->match = NULL;

        return s;
}

/* Copy original stack and return new stack's address.
 * if false, return NULL. */
stack *stackDup(stack *orig)
{
        stack *copy;
        stackNode *node;
        stackIter *iter;

        copy = stackCreate();
        copy->dup = orig->dup;
        copy->free = orig->free;
        copy->match = orig->match;

        iter = stackGetIter(orig);
        while ((node = stackNext(iter)) != NULL) {
                void *value;

                if (copy->dup) {
                        value = copy->dup(node->value);
                        if (value == NULL) {
                                stackRelease(copy);
                                stackReleaseIter(iter);
                                return NULL;
                        }
                } else
                        value = node->value;

                if (stackPush(copy, value) == NULL) {
                        stackRelease(copy);
                        stackReleaseIter(iter);
                        return NULL;
                }
        }
        stackReverse(copy);
        stackReleaseIter(iter);
        return copy;
}

/* Reverse stack. this function can't failed. */
void stackReverse(stack *s)
{
        stackNode *prev, *curr;

        prev = NULL;
        stackIter *iter = stackGetIter(s);
        while ((curr = stackNext(iter)) != NULL) {
                curr->next = prev;
                prev = curr;
        }
        s->top = prev;
}

/* Search stack node by key.
 * if not found, return NULL. */
stackNode *stackSearchKey(stack *s, void *key)
{
        stackIter *iter;
        stackNode *node;

        iter = stackGetIter(s);
        while ((node = stackNext(iter)) != NULL) {
                if (s->match) {
                        if (s->match(node->value, key)) {
                                stackReleaseIter(iter);
                                return node;
                        }
                } else {
                        if (key == node->value) {
                                stackReleaseIter(iter);
                                return node;
                        }
                }
        }
        stackReleaseIter(iter);
        return NULL;
}

/* Free all stackNode and stack itself. */
void stackRelease(stack *s)
{
        stackNode *node;
        stackIter *iter;

        iter = stackGetIter(s);
        while ((node = stackNext(iter)) != NULL) {
                if (s->free)
                        s->free(node->value);
                free(node);
        }
        free(s);
}

/* Create a stack Iterator and return address.
 * if false, reuturn NULL. */
stackIter *stackGetIter(stack *s)
{
        stackIter *iter;

        iter = malloc(sizeof(stackIter));
        if (iter == NULL)
                return NULL;
        iter->next = s->top;

        return iter;
}

/* Free stack Iterator. */
void stackReleaseIter(stackIter *iter)
{
        free(iter);
}

/* Let stack Iterator move to next node. */
stackNode *stackNext(stackIter *iter)
{
        stackNode *node;

        node = iter->next;
        if (node != NULL)
                iter->next = node->next;
        return node;
}

/* Push a integer into a stack.
 * if success, return stack address. else return NULL */
stack *stackPush(stack *s, void *value)
{
        stackNode *newNode;

        newNode = malloc(sizeof(stackNode));
        if (newNode == NULL)
                return NULL;
        newNode->value = value;
        newNode->next = s->top;
        s->top = newNode;
        s->len++;
        return s;
}

/* Pop value and return address.
 * if stack is empty, return NULL. */
void *stackPop(stack *s)
{
        void *popValue;
        stackNode *topNode;

        if (s->len == 0)
                return NULL;

        topNode = s->top;
        popValue = topNode->value;
        s->top = s->top->next;
        s->len--;
        free(topNode);

        return popValue;
}

/* Show all stack message. */
void stackDebug(stack *s)
{
        stackNode *node;
        stackIter *iter = stackGetIter(s);

        printf("length: %ld\n", stackSize(s));
        printf("top -> ");
        while ((node = stackNext(iter)) != NULL)
                printf("%d -> ", *(int *)node->value);
        printf("NULL\n");
}

void num_free(void *ptr)
{
        free(ptr);
}

void *num_dup(void *ptr)
{
        int *newnum;
        newnum = malloc(sizeof(int));
        *newnum = *(int *)ptr;

        return newnum;
}

int num_match(void *ptr, void *key)
{
        if (*(int *)ptr == *(int *)key)
                return 1;
        return 0;
}

/* This main function used for test and debug. */
int main(void)
{
        int *num;
        char opt[256];
        stackNode *node;
        stack *temp;
        stack *s = stackCreate();
        s->free = num_free;
        s->dup = num_dup;
        s->match = num_match;

        puts("This is stack test and debug.");
        puts("push [number]");
        puts("pop");
        puts("reverse");
        puts("dup");
        puts("search");
        puts("exit\n");

        scanf("%s", opt);
        while (strcmp(opt, "exit") != 0) {
                if (strcmp(opt, "push") == 0) {
                        num = malloc(sizeof(int));
                        scanf("%d", num);
                        stackPush(s, num);
                        stackDebug(s);
                        printf("\n");
                } else if (strcmp(opt, "pop") == 0) {
                        num = stackPop(s);
                        if (num == NULL) {
                                fprintf(stderr, "stack is empty.\n\n");
                        } else {
                                stackDebug(s);
                                printf("poped value is %d\n", *num);
                                printf("\n");
                                free(num);
                        }
                } else if (strcmp(opt, "reverse") == 0) {
                        stackReverse(s);
                        stackDebug(s);
                        printf("\n");
                } else if (strcmp(opt, "dup") == 0) {
                        temp = stackDup(s);
                        stackRelease(s);
                        s = temp;
                        stackDebug(s);
                        printf("\n");
                } else if (strcmp(opt, "search") == 0) {
                        num = malloc(sizeof(int));
                        scanf("%d", num);
                        node = stackSearchKey(s, num);
                        free(num);
                        if (node == NULL)
                                fprintf(stderr, "No this value in stack.\n");
                        else
                                printf("Yes %d in the stack.\n", *(int *)node->value);
                        printf("\n");
                } else {
                        puts("Invalid operation.\n");
                        fseek(stdin, 0, SEEK_END);
                }
                scanf("%s", opt);
        }

        stackRelease(s);
        return 0;
}
