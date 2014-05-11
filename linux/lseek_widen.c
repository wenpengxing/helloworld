#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void sys_err(char *str)
{
	perror(str);
	exit(-1);
}
int main(int argc, char *argv[])
{
	int fd;
	if (argc < 2) {
		printf("./a.out filename\n");
		exit(-1);
	}
	if ((fd = open(argv[1], O_RDWR)) < 0)
		sys_err("open");
	lseek(fd, 1000, SEEK_END);
	write(fd, "a", 1);
	close(fd);
	return 0;
}
