#include "common.h"

void err_sys(const char *str)
{
	perror(str);
	exit(1);
}

void err_usr(const char *str)
{
	fputs(str, stderr);
	exit(2);
}

void usage()
{
	printf("Usage: ./appname -index|-text|bin "
		"[-f usr_filename]\n");
	printf("-index\tIndex the dictionary.\n");
	printf("-text\trun the dictionary search "
		"using the text format dictionary\n");	
	printf("-bin\trun the dictionary search "
		"using the indexed format \n");
	printf("-f\tdictionary and user lexicon\n");	
}

void wrong_command(void)
{
	usage();
	err_usr("program quit...\n");
}
