#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main(void)
{
	printf("%s\n", ttyname(STDOUT_FILENO));
	return 0;
}
