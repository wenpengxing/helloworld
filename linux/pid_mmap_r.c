#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
struct STU {
	int id;
	char name[20];
	char sex;
};
int main(int argc, char *argv[])
{
	struct STU *mem;
	int fd;
	
	fd = open(argv[1], O_RDWR);
	mem = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	while (1) {
	printf("%d\n%s\n%c\n", mem->id, mem->name, mem->sex);
	sleep(2);
	}
	munmap(mem, 1024);
	close(fd);
	return 0;
}
