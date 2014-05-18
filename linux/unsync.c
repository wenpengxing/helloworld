#include <stdio.h>
#include <signal.h>
#include <string.h>
int num = 0;
void do_sig(int n)
{
	char str2[] = "hello world";
	strtok(str2, " ");
	printf("%s\n", str2);
}
int main(void)
{
	signal(SIGINT, do_sig);
	char str1[] = "akaedu good sfa a f";
	char *p;
	strtok(str1, " ");
	while ((p = strtok(NULL, " ")) != NULL) {
		printf("%s\n", p);
		sleep(1);
	}
}
