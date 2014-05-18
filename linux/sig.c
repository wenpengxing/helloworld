#include <stdio.h>
#include <signal.h>

void do_sig(int num)
{
	printf("hello world\n");
}
int main(void)
{
	signal(SIGINT, do_sig);
	signal(SIGQUIT, do_sig);
	signal(SIGTSTP, do_sig);
	while (1) {
		printf("****************\n");
		sleep(1);
	}
	return 0;
}
