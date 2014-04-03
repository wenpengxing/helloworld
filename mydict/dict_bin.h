#ifndef DICT_BIN_H_
#define DICT_BIN_H_

#include "dict.h"

#define LEN 256

typedef struct
{
	char header[LEN];
	int nword;
}head_t;

extern dict_t *dict_init_bin(const char *filename, dict_t *d); 
extern int create_idx(const char *t_filename, const char *b_filename);

#endif
