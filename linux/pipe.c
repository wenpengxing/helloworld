#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
void sys_err(char *str)
{
	perror(str);
	exit(-1);
}
int main(int argc, char *argv[])
{
	int fd[2], len;
	pid_t pid;
	char buf[4096];
	if (pipe(fd) != 0)	sys_err("pipe");
	pid = fork();
	if (pid < 0)	sys_err("fork");
	else if (pid == 0) {
		int flag;
		close(fd[1]);
		flag = fcntl(fd[0], F_GETFL);
		flag |= O_NONBLOCK;
		fcntl(fd[0], F_SETFL, flag);
		while (1) {
			if ((len = read(fd[0], buf, sizeof(buf))) > 0)
				write(STDOUT_FILENO, buf, len);
			write(STDOUT_FILENO, "child\n", 6);
			sleep(1);
		}
	}
	else {
		close(fd[0]);
		while (1) {	
			len = read(STDIN_FILENO, buf, sizeof(buf));
			write(fd[1], buf, len);
		}
	}
	return 0;
}
