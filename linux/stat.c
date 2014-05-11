#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	struct stat buf;
	if (argc < 2) {
		printf("./a.out filename\n");
		exit(-1);
	}
	stat(argv[1], &buf);
	printf("%s size : %d\n", argv[1], (int)buf.st_size);
	return 0;
}
