#ifndef STACK_H_
#define STACK_H_
extern void stack_init(int size);
extern int is_full(void);
extern void push(char item);
extern char pop(void);
extern int is_empty(void);
#endif
