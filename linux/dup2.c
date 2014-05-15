#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(void)
{
	int fd, fdsave;
	char buf[1024];
	fd = open("abc", O_RDWR);
	fdsave = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	scanf("%s", buf);
	printf("%s\n", buf);
	dup2(fdsave, STDIN_FILENO);
	close(fdsave);
	scanf("%s", buf);
	printf("%s\n", buf);
	return 0;
}
