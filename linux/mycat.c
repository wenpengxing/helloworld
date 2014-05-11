#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFSIZE 4096

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}
int main(int argc, char *argv[])
{
    int fd, n;
    char buf[BUFSIZE];
    if (argc < 2) {
        printf("./mycat file\n");
        exit(-1);
    }
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        sys_err("open");
    while (n = read(fd, buf, sizeof(buf))) {
        if (n < 0)
            sys_err("read");
        write(STDOUT_FILENO, buf, n);
    }
    write(STDOUT_FILENO, "\n", 1);
    close(fd);
    
    return 0;
}