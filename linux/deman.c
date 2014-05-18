#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
void daemonize(void)
{
	pid_t pid;
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	} else if (pid != 0) /* parent */
		exit(0);

	setsid();

	if (chdir("/") < 0) {
		perror("chdir");
		exit(1);
	}
	close(0);
	open("/dev/null", O_RDWR);
	dup2(0, 1);
	dup2(0, 2);
}
int main(void)
{
	char buf[1024];
	daemonize();
	int fd = open("/tmp/demeon.log", O_CREAT | O_RDWR | O_TRUNC, 0777);
	time_t t;
	while(1) {
		t = time(NULL);
		strcpy(buf, ctime(&t));
		write(fd, buf, strlen(buf));
		sleep(3);
	}
}

