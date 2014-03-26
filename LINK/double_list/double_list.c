#include <stdio.h>
#include <stdlib.h>
#include "double_list.h"
void init_double(link *head, link *tail)
{
	*head = make_node(0);
	*tail = make_node(0);
	(*head)->next = *tail;
	(*tail)->pre = *head;
}
link make_node(unsigned int item)
{
	link p = malloc(sizeof *p);
	p->item = item;
	p->next = NULL;
	p->pre = NULL;
	return p;
}
void free_node(link p)
{
	free(p);
}
link search(link *head, link *tail, unsigned int key)
{
	link p;
	for (p = (*head)->next; p != *tail; p = p->next)
		if (p->item == key)
			return p;
	return NULL;
}
void insert_head(link *head, link p)
{
	p->next = (*head)->next;
	(*head)->next->pre = p;
	(*head)->next = p;
	p->pre = *head;
}
void delete(link p)
{

	p->pre->next = p->next;
	p->next->pre = p->pre;
}
void traverse_head(link *head, link *tail, void (*visit)(link))
{
	link p;
	for (p = (*head)->next; p != *tail; p = p->next)
		visit(p);
}
void destroy(link *head, link *tail)
{
	link q, p = (*head)->next;
	while (p != *tail) {
		q = p;
		p = p->next;
		free_node(q);
	}
}
int destroy_double(link *head, link *tail)
{
	if ((*head)->next == *tail && (*tail)->pre == *head) {
		free_node(*head);
		free_node(*tail);
		*head = *tail = NULL;
		return 0;
	}
	return -1;
}
void swap(link m, link n)
{
	n->next->pre = m;
	n->pre = m->pre;
	m->pre->next = n;
	m->pre = n;
	m->next = n->next;
	n->next = m;
}
void sort_double(link *head, link *tail)
{
	link p, q, m, tmp;
	for (p = *tail; p != (*head)->next; p = p->pre)
		for (m = (*head)->next; m != p->pre; m = m->next) {
			q = m;
			if (q->item > q->next->item) {
				swap(q, q->next);
				m = q->pre;
			}
		}
}

