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
    int fdsrc, fddest, n;
    char buf[BUFSIZE];
    if (argc < 3) {
        printf("./mycp src dest\n");
        exit(-1);
    }
    if ((fdsrc = open(argv[1], O_RDONLY)) < 0)
        sys_err("open");
    if ((fddest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0777)) < 0)
        sys_err("open");
    while (n = read(fdsrc, buf, sizeof(buf))) {
        if (n < 0)
            sys_err("read");
        write(fddest, buf, n);
    }
    close(fdsrc);
    close(fddest);
    
    return 0;
}