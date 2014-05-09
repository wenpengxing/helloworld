#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void)
{
	int fd, i = 3;
	int len;
	fd = open("abc", O_CREAT);
	printf("fd = %d\n", fd);
	return 0;
}
