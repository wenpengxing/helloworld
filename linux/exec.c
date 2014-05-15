#include <stdio.h>
#include <unistd.h>

int main(void)
{
	execlp("./bb", "ahahaha", "3", "akaedu", NULL);
	return 0;
}
