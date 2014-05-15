#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(void)
{
	int fd, fdsave, fd2, stdinsave;
	stdinsave = dup(STDIN_FILENO);
	close(0);
	fd2 = open("abc", O_RDWR);	
	fd = dup(STDOUT_FILENO);
	printf("fd = %d\n", fd);
	write(fd, "helloworld\n", 11);
	scanf("%d", &fdsave); //read(0,)
	printf("%d\n", fdsave);
	close(fd2);
	dup(stdinsave);
	scanf("%d", &fdsave); //read(0,)
	printf("%d\n", fdsave);
	close(fd);
	return 0;
}
