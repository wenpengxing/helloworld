#ifndef STACK_H_
#define STACK_H_
extern int stack[512];
extern int top;
extern void push(int num);
extern int pop(void);
extern int is_empty(void);
#endif
