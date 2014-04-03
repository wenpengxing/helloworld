#ifndef ERR_H_
#define ERR_H_

#include <stdio.h>
#include <stdlib.h>

extern void err_sys(const char *str);
extern void err_usr(const char *str);
extern void usage(void);
extern void wrong_command(void);

#endif
