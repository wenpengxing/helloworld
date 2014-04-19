#include <stdio.h>
#include <stdlib.h>
#include "single_list.h"
void init_single(link *head)
{
    *head = NULL;
}
link make_node(unsigned int item)
{
    link p = (link)malloc(sizeof *p);
	p->item = item;
	p->next = NULL;
	return p;
}
void free_node(link p)
{
    free(p);
}
link search(link *head, unsigned int key)
{
    link p;
	for (p = *head; p; p = p->next)
		if (p->item == key)
			return p;
	return NULL;
}
void insert(link *head, link p)
{
    p->next = *head;
	*head = p;
}
void delete(link *head, link p)
{
    link pre;
	if (p == *head) {
		*head = p->next;
		return;
	}
	for (pre = *head; pre; pre = pre->next)
		if (pre->next == p) {
			pre->next = p->next;
			return;
		}
}
void traverse(link *head, void (*visit)(link))
{
    link p;
	for (p = *head; p; p = p->next)
		visit(p);
}

void destroy(link *head)
{
    link q, p = *head;
	*head = NULL;
	while (p) {
		q = p;
		p = p->next;
		free_node(q);
	}
}
void sort_single(link *head)
{
}

