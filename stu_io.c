#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct STU {
	int id;
	char name[20];
	char sex;
};
int read_file(FILE *fp, struct STU *a, int n)
{
	int i;
	char buf[100];
	for (i = 0; i < n; i++) {
		fgets(buf, sizeof(buf), fp);
		a[i].id = atoi(strtok(buf, "\n"));

		fgets(buf, sizeof(buf), fp);
		strcpy(a[i].name, strtok(buf, "\n"));

		fgets(buf, sizeof(buf), fp);
		a[i].sex = buf[0];
	}
	return i;
}
int cnt_stu(FILE *fp)
{
	int n = 0;
	char buf[100];
	while (fgets(buf, sizeof(buf), fp))
		n++;
	return n/3;
}
void show_stu(struct STU *a, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d\t%s\t%c\n", a[i].id, a[i].name, a[i].sex);

}
void swap(struct STU *m, struct STU *n)
{
	struct STU tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}
void sort_stu(struct STU *a, int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n-i-1; ++j)
			if (a[j].id > a[j+1].id)
				swap(&a[j], &a[j+1]);
}
int write_file_bin(FILE *fp, struct STU *a, int n)
{
	int i;
	//how many student num
	fwrite(&n, sizeof(int), 1, fp);
	for (i = 0; i < n; ++i)
		fwrite(&a[i], sizeof(struct STU), 1, fp);
	return i;
}
int read_file_bin(FILE *fp, struct STU *a, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		fread(&a[i], sizeof(struct STU), 1, fp);
	return i;
}
int read_file_bin_head(FILE *fp)
{
	int n = 0;
	fread(&n, sizeof(int), 1, fp);
	return n;
}
int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("./a.out stufile stufile_bin\n"
				"or ./a.out stufile_bin\n");
		exit(-1);
	}
	int n;
	if (strcmp(argv[1], "stufile") == 0) {
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL) {
			perror(argv[1]);
			exit(-1);
		}
		FILE *fp_bin = fopen(argv[2], "w");
		if (fp_bin == NULL) {
			perror(argv[2]);
			exit(-1);
		}
		n = cnt_stu(fp);
#ifdef DEBUG
		printf("n = %d\n", n);
#endif
		struct STU a[n];
		rewind(fp);
		read_file(fp, a, n);
		sort_stu(a, n);
		show_stu(a, n);
		write_file_bin(fp_bin, a, n);
		fclose(fp);
		fclose(fp_bin);
	}
	else if (strcmp(argv[1], "stufile_bin") == 0) {
		FILE *fp = fopen(argv[1], "r");
		int n = read_file_bin_head(fp);
		struct STU a[n];
		read_file_bin(fp, a, n);
		show_stu(a, n);
		fclose(fp);
	}

	return 0;
}
