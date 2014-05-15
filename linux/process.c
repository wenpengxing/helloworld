#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main(void)
{
	pid_t pid;
	int n = 2;
	while (n--) {
		if ((pid = fork()) < 0) {
			perror("fork");
			exit(-1);
		}
		else if (pid == 0)
			break;
	}
	if ((pid == 0) && (n == 1)) {
		execlp("firefox", "firefox", "www.sina.com.cn", NULL);
		exit(-1);
	}
	if ((pid == 0) && (n == 0)) {
		execlp("eog", "eog", "/home/xwp/桌面/进程.jpg", NULL);
		exit(-1);
	}
	while (waitpid(-1, NULL, WNOHANG) >= 0) {
		printf("I am parent\n");
		sleep(1);
	}
	return 0;
}
