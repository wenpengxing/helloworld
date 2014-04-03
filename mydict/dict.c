#include "common.h"

static int get_word_num(FILE *fp)
{
	char buf[BUF_SIZE];
	int n = 0;

	while(fgets(buf, BUF_SIZE, fp)){
		if(buf[0] == '#')
			n++;
	}

	return n;
}
static void merge(ditem_t *arr,int start,int mid,int end){

	int n1 = mid - start + 1;
	int n2 = end - mid;
	ditem_t	left[n1],right[n2];
	int i,j,k;

	for(i=0;i<n1;i++)left[i] = arr[start + i];
	for(j=0;j<n2;j++)right[j] = arr[mid + 1 + j];

	i = j = 0;
	k = start;

	while(i < n1 && j < n2){
		if(strcmp(left[i].key_word, right[j].key_word) < 0)arr[k++] = left[i++];
		else arr[k++] = right[j++];
	}

	while(i < n1)arr[k++] = left[i++];
	while(j < n2)arr[k++] = right[j++];

}
void combine_sort(ditem_t *arr,int start,int end){

	int mid;
	if(start < end){
	
		mid = (start + end)/2;
		combine_sort(arr,start,mid);
		combine_sort(arr,mid + 1,end);
		merge(arr,start,mid,end);
	}
}
void dict_free(dict_t *d)
{
	int i;

	if(d->dict != NULL){
		for(i = 0; i < d->nword; i++)
			free_item(&(d->dict[i]));
		free(d->dict);
	}
	d->nword = 0;
}

dict_t *dict_init_txt(const char *filename, dict_t *d)
{
	FILE *fp; char buf[BUF_SIZE];
	static dict_t bakup; int i;
	char key[WLEN]; char trans[BUF_SIZE];

	if(d == NULL)
		d = &bakup;
	fp = fopen(filename, "r");
	if(fp == NULL)
		return NULL;

	d->nword = get_word_num(fp); 
	rewind(fp); /* back to beginning */
	
	d->dict = (ditem_t *)malloc(sizeof(ditem_t) * d->nword);
	if(d->dict == NULL)
		return NULL;
	memset(d->dict, 0, sizeof(ditem_t) * d->nword);

	i = -1;
	trans[0] = '\0'; key[0] = '\0';
	while(fgets(buf, BUF_SIZE, fp)){
		if(buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		if(buf[0] == '#'){
			strcpy(key, &buf[1]);
			i++;
		}else
			strcpy(trans, &buf[6]);
		if(key[0] != '\0'){
			set_key_word(&d->dict[i], key);
			key[0] = '\0';
		}
		if(trans[0] != '\0'){
			set_trans(&d->dict[i], trans);	
			trans[0] = '\0';	
		}		
	}
	fclose(fp);

	/* make sure the words in order */
	
	return d;
}
ditem_t *dict_search(const char *key, const dict_t *d)
{
	int start, end, mid;
	int res;

	if(d == NULL)
		return NULL;
	if(d->dict == NULL)
		return NULL;

	start = 0, end = d->nword - 1;
	while(start <= end){

		mid = (start + end) / 2;

		res = strcmp(key, d->dict[mid].key_word);
		if(res == 0)
			break;
		else if(res > 0)

			start = mid + 1;
		else

			end = mid - 1;
	}
	if(start > end)
		return NULL;
	return &d->dict[mid];
}
