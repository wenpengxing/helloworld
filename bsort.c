#include <stdio.h>
#include <string.h>

void bsort(void *a, int nmemb, int nsize, int compar(void *, void *))
{
	int i, j;
	char tmp[nsize];
	for (i = 0; i < nmemb; i++)
		for (j = 0; j < nmemb-i-1; j++)
			if (compar((void *)((char *)a+j*nsize), 
						(void *)((char *)a+(j+1)*nsize)) > 0) {
				memcpy((void *)(tmp), (void *)((char *)a+j*nsize),nsize);
				memcpy((void *)((char *)a+j*nsize), (void *)((char *)a+(j+1)*nsize), nsize);
				memcpy((void *)((char *)a+(j+1)*nsize), (void*)tmp, nsize);
			}
}
int int_cmp(void * a, void * b)
{
	int m = *((int*)a);
	int n = *((int*)b);
	if (m > n)
		return 1;
	else if (m == n)
		return 0;
	else 
		return -1;
}
void show_int(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d\n", a[i]);
}
void show_str(char *b[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%s\n", b[i]);
}
int str_cmp(void *a, void *b)
{
	//char *m = (char *)(*((int *)a));
	//char *n = (char *)(*((int *)b));
	char *m = *((char **)a);
	char *n = *((char **)b);
	return strcmp(m, n);
}
int main(void)
{
	int a[5] = {33,1,5,9,2};
	char *b[5] = {"abc", "world", "aka", "hello", "good"};
	bsort((void*)a, 5, sizeof(a[0]), int_cmp);
	show_int(a, 5);
	bsort((void*)b, 5, sizeof(b[0]), str_cmp);
	show_str(b, 5);
	return 0;
}
