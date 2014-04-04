#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int *S;
static int top;
static int size;
void init_stack(int sz)
{
	size = sz;
	S = malloc(size*sizeof(int));
	top = 0;
}
void push(int item) { S[top++] = item; }
int pop() { return S[--top]; }
int eval(char *s)
{
	int i, n=strlen(s);
	init_stack(n);
	for (i=0; i<n; i++) {
		if (s[i]>='0'&&s[i]<='9') 
			push(0);
		while (s[i]>='0'&&s[i]<='9') 
			push(10*pop()+s[i++]-'0');
		if (s[i]=='+') push(pop()+pop());
		if (s[i]=='*') push(pop()*pop());
	}
	return pop();
}
int main()
{
	printf("%d\n", eval("10 20 + 30 40 + *"));
	return 0;
}
