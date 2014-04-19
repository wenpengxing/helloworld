#include <stdio.h>
#include "single_list.h"

void print_item(link p)
{
	printf("%d\n", p->item); 
}

int main(void)
{
    link head;
    init_single(&head);
	link p = make_node(10);
	insert(&head, p);
	p = make_node(5);
	insert(&head, p);
	p = make_node(90);
	insert(&head, p);
	p = search(&head, 5);
	delete(&head, p);
	free_node(p);
	traverse(&head, print_item);
	destroy(&head);

	return 0;
}
