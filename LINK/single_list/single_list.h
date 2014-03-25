#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

typedef struct node *link;
struct node {
	unsigned int item;
	link next;
};

void init_single(link *head);
link make_node(unsigned char item);
void free_node(link p);
link search(link *head, unsigned char key);
void insert(link *head, link p);
void delete(link *head, link p);
void traverse(link *head, void (*visit)(link));
void destroy(link *head);
void sort_single(link *head);

#endif