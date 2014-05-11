#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char buf[1024];
	scanf("%s", buf);
	printf("%s", buf);

	//stdout   STDOUT_FILENO
	//printf("helloworld\n");
	/*
	int fd;
	close(STDOUT_FILENO);
	fd = open(argv[1], O_WRONLY);
	write(STDOUT_FILENO, "helloworld", 10);
	*/
	return 0;
}
