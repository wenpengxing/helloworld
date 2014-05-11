#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd, len;
	if (argc < 2) {
		printf("./a.out filename\n");
		exit(-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(-1);
	}
	len = lseek(fd, 0, SEEK_END);
	printf("%s size: %d\n", argv[1], len);
	close(fd);
	return 0;
}
