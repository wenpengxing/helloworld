#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	pid_t pid;
	int sig;
	if (argc < 3) {
		printf("./mykill signal pid\n");
		exit(-1);
	}
	sig = atoi(argv[1]);
	pid = atoi(argv[2]);

	kill(pid, sig);
	return 0;
}
