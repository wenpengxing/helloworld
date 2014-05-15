#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	pid_t pid;
	int n = atoi(argv[1]);
	while (n--) {
		if ((pid = fork()) < 0) {
			perror("fork");
			exit(-1);
		}
		else if (pid == 0) 
			break;
		else {
			printf("creat child %d\n", pid);
		}
	}
	if (pid == 0) {
		srand(time(NULL)*n);
		int m = rand() % 10;
		while (m--) {
	//	while (1) {
			printf("I am child %d, my parent %d\n", getpid(), getppid());
			sleep(1);
		}
	}
	else {
		pid_t childid;
		while (1) {
			if ((childid = waitpid(-1, NULL, WNOHANG)) > 0) 
				printf("child %d is over\n", childid);
			else {
				printf("I am parent, wait for child\n");
				sleep(1);
			}
		}
	}
	return 0;
	}
