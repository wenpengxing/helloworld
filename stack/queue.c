#include <stdlib.h>
static int head, tail;
static int *queue;
static int sz;

void init_queue(int size)
{
	if (size == 0) {
		sz = 512;
		size = sz;
	}
	sz = size;
	queue = (int *)malloc(sz * sizeof(int));
	head = tail = 0;
}
void destroy_queue(void)
{
	free(queue);
}
void enqueue(int item)
{
	queue[tail++%sz] = item;
}
int dequeue(void)
{
	return queue[head++%sz];
}
int is_empty(void)
{
	return head == tail;
}
int is_full(void)
{
	return ((tail % sz) == (head%sz))  && (head != tail);
}
