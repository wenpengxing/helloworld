#include <stdio.h>
#include <signal.h>
void do_sigint(int num)
{
	printf("num = %d  helloworld\n", num);
}
int main(void)
{
	struct sigaction act, oldact;

	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGHUP, &act, &oldact);
	while (1) {
		sleep(1);
	}
	return 0;
}
