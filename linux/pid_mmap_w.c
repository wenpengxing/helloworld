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
	int fd, i = 10;

	fd = open(argv[1], O_CREAT|O_RDWR, 0777);
	lseek(fd, 1023, SEEK_SET);
	write(fd, "\0", 1);
	while (1) {
		mem = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		mem->id = i;
		strcpy(mem->name ,"xiaoming");
		mem->sex = 'm';
		sleep(2);
		i++;
	}
	munmap(mem, 1024);
	close(fd);

	return 0;
}
