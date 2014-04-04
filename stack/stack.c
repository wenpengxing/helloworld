#include <stdlib.h>
static char *stack = NULL;
static int top = -1;
static int sz = 512;
void stack_init(int size)
{
	if (size == 0)	size = sz;
	else			sz= size;
	stack = (char *)malloc(size);
}
void push(char item)
{
	if (is_full())
		stack = (char *)realloc(stack, sz+=sz);
	stack[++top] = item;
}
char pop(void)
{
	return stack[top--];
}
int is_empty(void)
{
	return top == -1;
}
int is_full(void)
{
	return top == sz-1;
}
void stack_destroy(void)
{
	free(stack);
}
