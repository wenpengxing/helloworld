#ifndef QUEUE_H_
#define QUEUE_H_
void init_queue(int size);
void destroy_queue(void);
void enqueue(int item);
int dequeue(void);
int is_empty(void);
int is_full(void);
#endif
