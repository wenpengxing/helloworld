#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	pid_t pid;
	int i = 0;
	pid = fork();
	if (pid == 0) {
		while (1) {
			printf("%d I am child %d, my parent %d\n", getpid(),i++, getppid());
			sleep(1);
		}
	}
	else if (pid > 0) {
	//	while (1) {
			printf("%d I am parent %d, my child %d, my parent %d\n", getpid(),i++, pid, getppid());
			sleep(3);
	//	}
	}
	else {
		perror("fork");
		exit(-1);
	}
	return 0;
}
