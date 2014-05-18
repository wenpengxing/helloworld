#include <stdio.h>

int main(void)
{
	while (1) {
		system("date");
		// fork   exec wait
		sleep(1);
	}
}
