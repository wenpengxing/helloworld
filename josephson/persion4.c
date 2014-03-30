#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct persion {
	char *name;
	int age;
	char sex;
	int n_insterest;
	char **insterest;
};
void show_persion(struct persion a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		printf("%s\t%d\t%c\t%d\t", a[i].name, a[i].age, a[i].sex, a[i].n_insterest);
		for (j = 0; j < a[i].n_insterest; j++)
			printf("%s\t", a[i].insterest[j]);
		printf("\n");
	}
}
void destroy(struct persion *p, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		free(p[i].name);
		for (j = 0; j < p[i].n_insterest; j++)
			free(p[i].insterest[j]);
		free(p[i].insterest);
	}
	free(p);
}
void persion_init(FILE *fp, struct persion *p, int n)
{
	int i = 0,j, len, m = 0;
	char buf[4096], *tmp, *s;
	while (fgets(buf, sizeof(buf), fp) && i < n) {
		tmp = strtok(buf, " \t");
		len = strlen(tmp);
		p[i].name = malloc(len+1);
		strcpy(p[i].name, tmp);
		p[i].age = atoi(strtok(NULL, " \t"));
		tmp = strtok(NULL, " \t");
		p[i].sex = *tmp;
		tmp = strtok(NULL, " \t\n"); // run@football
		m = 1;
		s = tmp;
		while ((s = strchr(s, '@'))) {
			m++;
			s++;
		}
		p[i].n_insterest = m;
		p[i].insterest = malloc(p[i].n_insterest*sizeof(char *));
		j = 0;
		while ((s = strtok_r(tmp, "@", &tmp)) && (j < p[i].n_insterest)) {
			p[i].insterest[j] = malloc(strlen(s)+1);
			strcpy(p[i].insterest[j], s);
			j++;
		}
		i++;
	}
}
int line_cnt(FILE *fp)
{
	int n = 0;
	char buf[4096];
	while (fgets(buf, sizeof(buf), fp))
		n++;
	return n;
}
FILE *FOPEN(char *path, char *mode)
{
	FILE *fp = fopen(path, mode);
	if (fp == NULL) {
		perror(path);
		exit(-1);
	}
	return fp;
}
void sort_by_name(struct persion a[], int n)
{
	struct persion tmp;
	int i, j; 
	for (i = 0; i < n; i++)
		for (j = 0; j < n-i-1; j++)
			if (strcmp(a[j].name, a[j+1].name) > 0) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
}
int main(void)
{
	int n = 0;
	FILE *fp = FOPEN("persion", "r");
	n = line_cnt(fp);
	struct persion *p = calloc(n, sizeof(struct persion));
	rewind(fp);
	persion_init(fp, p, n);
	show_persion(p, n);
	sort_by_name(p, n);
	show_persion(p, n);
	destroy(p, n);
	fclose(fp);
	return 0;
}
