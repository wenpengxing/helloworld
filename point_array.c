#include <stdio.h>
#include <string.h>
void fun_cat(char *s1, char *s2)
{
	printf("%s\n", strcat(s1, s2));
}
void fun_cmp(char *s1, char *s2)
{
	printf("%d\n", strcmp(s1, s2));
}
void fun_cpy(char *s1, char *s2)
{
	printf("%s\n", strcpy(s1, s2));
}
/*
typedef void (*FUN)(char *, char *);
FUN p[3];
*/
/* 
   练习：定义以下函数的函数指针数组?
   char *foo(int *n, char **m) 
   解答：typedef char *(*FUN)(int *, char **)
		 FUN p[3];
   练习：如果foo(int n)的函数返回值是一个函数指针
   char (*)(char *, int)类型,foo函数如何定义?
   解答：typedef char (*FUN)(char *, int)
		 FUN foo(int n)
   练习：上题foo函数的函数指针数组如何定义? 
   解答：FUN (*p[3])(int);
 */
int main(int argc, char *argv[])
{
	void (*p[3])(char *, char *) = {fun_cat, fun_cmp, fun_cpy};
	char s1[100] = "hello";
	char s2[100] = "world";
	p[0](s1, s2);
	p[1](s1, s2);
	p[2](s1, s2);
	return 0;
}
