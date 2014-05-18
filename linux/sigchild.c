#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void sys_err(char *str)
{
	perror(str);		exit(-1);
}
void do_sig(int num)
{
//	wait(NULL);
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}
int main(void)
{
	pid_t pid;
	int i;
	for (i = 0; i < 5; i++) {
		if ((pid = fork()) < 0) {
			sys_err("fork");
		}
		else if (pid == 0)	break;
	}
	if (pid == 0) {
		int n = 0;
		while (n <= 2) {
		printf("I am child %d\n", getpid());	sleep(1);  n++;
		}
	}
	else if (pid > 0) {
		signal(SIGCHLD, do_sig);
		while (1) {
			printf("I am parent\n");
			sleep(1);
		}
	}
	return 0;
}
