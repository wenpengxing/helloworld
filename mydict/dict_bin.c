#include "common.h"

static int read_idx_dict(const char *idx_filename, dict_t *d)
{
	FILE *fp; head_t h; 
	int i, j, len, tnum;
	char key[WLEN]; char trans_line[BUF_SIZE];
	char *p; int tlen;

	if(d == NULL)
		return FALSE;
	fp = fopen(idx_filename, "r");
	if(fp == NULL)
		return FALSE;

	fread(&h, sizeof(h), 1, fp);
	//DEBUG_PRINT0(h.header);
	printf("bin %d\n", h.nword);
	d->nword = h.nword;
	d->dict = (ditem_t *)malloc(sizeof(ditem_t) * d->nword);
	if(d->dict == NULL)
		return FALSE;
	
	for(i = 0; i < d->nword; i++){
		fread(&len, sizeof(len), 1, fp);
		fread(key, sizeof(char), len, fp);
		key[len] = '\0';
		set_key_word(&d->dict[i], key);
		
		fread(&tnum, sizeof(tnum), 1, fp);
		d->dict[i].trans_num = tnum;

		p = trans_line; tlen = 0;
		for(j = 0; j < tnum; j++){
			fread(&len, sizeof(len), 1, fp);
			fread(p, sizeof(char), len, fp);
			p[len] = '@'; 
			p += len; tlen += len;
		}
		trans_line[tlen] = '\0';
		set_trans(&d->dict[i], trans_line);
	}

	fclose(fp);

	return TRUE;
}

dict_t *dict_init_bin(const char *filename, dict_t *d)
{
	static dict_t bakup;
	
	if(d == NULL)
		d = &bakup;
	if(read_idx_dict(filename, d) == FALSE)
		return NULL;

	return d;
}

int create_idx(const char *t_filename, const char *b_filename)
{
	dict_t d; FILE *fp;
	head_t h; int i, j, len;

	if(dict_init_txt(t_filename, &d) == NULL)
		return FALSE;
	fp = fopen(b_filename, "w");
	if(fp == NULL){
		dict_free(&d);
		return FALSE;
	}
	
	h.nword = d.nword;
	strcpy(h.header, "Dictionary Index Date, made by nomoon");
	fwrite(&h, sizeof(h), 1, fp);
	
	for(i = 0; i < d.nword; i++){
		len = strlen(d.dict[i].key_word);
		fwrite(&len, sizeof(len), 1, fp);
		fwrite(d.dict[i].key_word, sizeof(char), len, fp);
		fwrite(&d.dict[i].trans_num, sizeof(int), 1, fp);
		for(j = 0; j < d.dict[i].trans_num; j++){
			if(d.dict[i].trans[j] != NULL){
				len = strlen(d.dict[i].trans[j]);
				fwrite(&len, sizeof(len), 1, fp);
				fwrite(d.dict[i].trans[j], sizeof(char), len, fp);
			}else{
				len = 0;
				fwrite(&len, sizeof(len), 1, fp);
			}
		}

	}

	fclose(fp);
	dict_free(&d);

	return TRUE;
}
