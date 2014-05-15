#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
void sys_err(char *str)
{
	perror(str);
	exit(-1);
}
int main(void)
{
	int fd[2][2], flag;
	char *whattime = "what is time?\n";
	char buf[1024];
	pid_t pid;
	if ((pipe(fd[0])<0) || (pipe(fd[1])<0))
		sys_err("pipe");
	if ((pid = fork()) < 0)
		sys_err("fork");
	else if (pid == 0) {
		int len;
		time_t t;
		close(fd[0][1]); close(fd[1][0]);
		flag = fcntl(fd[0][0], F_GETFL);	
		flag |= O_NONBLOCK;
		fcntl(fd[0][0], F_SETFL, flag);	
		while (1) {
			printf("I am child\n");
			sleep(2);
			if ((len = read(fd[0][0], buf, sizeof(buf))) > 0) {
				if (0 == strcmp(buf, whattime)) {
					t = time(NULL);
					strcpy(buf, ctime(&t));
					write(fd[1][1], buf, strlen(buf)+1);
				}
			}
		}
	}
	else
	{
		int n = 0, len;
		close(fd[0][0]); close(fd[1][1]);
		flag = fcntl(fd[1][0], F_GETFL);	
		flag |= O_NONBLOCK;
		fcntl(fd[1][0], F_SETFL, flag);	
		srand(time(NULL));
		while (1) {
			n = rand() % 10 + 1;
			while (n--) {
				printf("I am parent\n");
				sleep(1);
				if (n == 0) {
					write(fd[0][1], whattime, strlen(whattime)+1);
				}
				if ((len = read(fd[1][0], buf, sizeof(buf))) > 0)
					write(STDOUT_FILENO, buf, len);
			}
		}
	}
	return 0;
}
