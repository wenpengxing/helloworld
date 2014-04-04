#include <stdio.h>
#include "queue.h"
int main(void)
{
	int i;
	init_queue(3);

	for (i = 0; 1; i++) {
		if (is_full())
			break;
		enqueue(i);
	}

	while (!is_empty())
		printf("%d\n", dequeue());

	return 0;
}
