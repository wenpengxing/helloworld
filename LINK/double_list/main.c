#include <stdio.h>
#include "double_list.h"

void print_item(link p)
{
	printf("%d\n", p->item); 
}

int main(void)
{
    link head, tail;
    init_double(&head, &tail);
	link p = make_node(10);
	insert_head(&head, p);
	p = make_node(5);
	insert_head(&head, p);
	p = make_node(90);
	insert_head(&head, p);
	p = make_node(30);
	insert_head(&head, p);
	p = make_node(40);
	insert_head(&head, p);
	p = search(&head, &tail, 5);
//	delete(p);
//	free_node(p);
	traverse_head(&head, &tail, print_item);
	sort_double(&head, &tail);
	traverse_head(&head, &tail, print_item);
	destroy(&head, &tail);
    destroy_double(&head, &tail);

	return 0;
}
