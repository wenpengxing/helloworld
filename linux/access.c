#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	if (access("hello", W_OK) == 0)
		printf("can be read\n");
	return 0;
}
