#ifndef __STACK_H__
#define __STACK_H__

typedef struct stackNode {
	void *value;
	struct stackNode *next;
} stackNode;

typedef struct stack {
	stackNode *top;
	void *(*dup)(void *ptr);
	void (*free)(void *ptr);
	int (*match)(void *ptr, void *key);
	unsigned long len;
} stack;

typedef struct stackIter {
	stackNode *next;
} stackIter;

stack *stackCreate(void);
void stackRelease(stack *s);
stack *stackDup(stack *s);
void stackReverse(stack *s);
stackNode *stackSearchKey(stack *s, void *key);
stack *stackPush(stack *s, void *value);
void *stackPop(stack *s);
void stackDebug(stack *s);

stackIter *stackGetIter(stack *s);
void stackReleaseIter(stackIter *iter);
stackNode *stackNext(stackIter *iter);

#define stackPeek(s) ((s)->top->value)
#define stackSize(s) ((s)->len)

#endif /* __STACK_H__ */
