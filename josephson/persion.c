#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct persion {
	int age;
	char sex;
	char *name;
	char *insterest;
};
void show_persion(struct persion a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%s\t%d\t%c\t%s\n", a[i].name, a[i].age, a[i].sex, a[i].insterest);
}
void destroy(struct persion *p, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		free(p[i].name);
		free(p[i].insterest);
	}
	free(p);
}
void persion_init(FILE *fp, struct persion *p, int n)
{
	int i = 0, len;
	char buf[4096], *tmp;
	while (fgets(buf, sizeof(buf), fp) && i < n) {
		tmp = strtok(buf, " \t");
		len = strlen(tmp);
		p[i].name = malloc(len+1);
		strcpy(p[i].name, tmp);
		p[i].age = atoi(strtok(NULL, " \t"));
		tmp = strtok(NULL, " \t");
		p[i].sex = *tmp;
		tmp = strtok(NULL, " \t\n");
		len = strlen(tmp);
		p[i].insterest = malloc(len+1);
		strcpy(p[i].insterest, tmp);
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
int main(void)
{
	int n = 0;
	FILE *fp = FOPEN("persion", "r");
	n = line_cnt(fp);
	struct persion *p = calloc(n, sizeof(struct persion));
	rewind(fp);
	persion_init(fp, p, n);
	show_persion(p, n);
	destroy(p, n);
	fclose(fp);
	return 0;
}
