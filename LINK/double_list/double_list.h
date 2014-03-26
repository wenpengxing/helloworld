#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

typedef struct node *link;
struct node {
	unsigned int item;
	link next;
	link pre;
};

void init_double(link *head, link *tail);
link make_node(unsigned int item);
void free_node(link p);
link search(link *head, link *tail, unsigned int key);
void insert_head(link *head, link p);
void delete(link p);
void traverse_head(link *head, link *tail, void (*visit)(link));
void destroy(link *head, link *tail);
int destroy_double(link *head, link *tail);
void sort_double(link *head, link *tail);

#endif