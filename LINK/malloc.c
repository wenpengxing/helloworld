#include <stdio.h>
#include <stdlib.h>
int init_array(int a[], int n)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < n; ++i)
		a[i] = rand() % 100;
}
void show_array(int a[], int n)
{
	int i; 
	for (i = 0; i < n; ++i)
		printf("%4d", a[i]);
	printf("\n");
}
void sort_array(int a[], int n)
{
	int i, j, tmp;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n-i-1; ++j)
			if (a[j] > a[j+1]) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
}
int main(int argc, char *argv[])
{
	char buf[100];
	int m, n = atoi(argv[1]);
	int *a = calloc(n, sizeof(int));
	init_array(a, n);
	sort_array(a, n);
	show_array(a, n);
	gets(buf);
	// n = 10  m = 30
	m = atoi(buf);
	a = realloc(a, m*sizeof(int));
	init_array(a+n, m-n);
	sort_array(a, m);
	show_array(a, m);
	free(a);
	return 0;
}
