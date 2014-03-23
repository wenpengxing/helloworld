#include <stdio.h>
#include <stdlib.h>
	/*
	1.定义两个文件流指针，FILE *srcfp，*destfp
	2.只读方式打开原文件
	3.只写的方式打开目标文件
	4.循环读原文件和写目标文件，利用fgets每次都1行,fputs每次写1行
	5.关闭原文件和目标文件
	*/
#if 0
int main(int argc, char *argv[])
{
	FILE *srcfp, *destfp;
	char buf[8192];
	if (argc < 3) {
		printf("./mycp src dest\n");	return -1;
	}
	srcfp = fopen(argv[1], "r");
	if (srcfp == NULL) {
		perror(argv[1]);	exit(-1);
	}
	destfp = fopen(argv[2], "w");
	if (destfp == NULL) {
		perror(argv[2]);	exit(-1);
	}
	while (fgets(buf, sizeof(buf), srcfp))
		fputs(buf, destfp);
	fclose(srcfp);	fclose(destfp);
	return 0;
}
#endif
#if 0
//从普通文件读，写到标准输出
int main(int argc, char *argv[])
{
	FILE *srcfp;
	char buf[8192];
	srcfp = fopen(argv[1], "r");
	if (srcfp == NULL) {
		perror(argv[1]);	exit(-1);
	}

	while (fgets(buf, sizeof(buf), srcfp))
		fputs(buf, stdout);
	fclose(srcfp);
	return 0;
}
#endif
#if 0
//从标准输入读，写到普通文件里
int main(int argc, char *argv[])
{
	FILE *srcfp;
	char buf[8192];
	srcfp = fopen(argv[1], "w");
	if (srcfp == NULL) {
		perror(argv[1]);	exit(-1);
	}
	while (fgets(buf, sizeof(buf), stdin))
		fputs(buf, srcfp);
	fclose(srcfp);
	return 0;
}
#endif
#if 0
int main(int argc, char *argv[])
{
	FILE *srcfp, *destfp;
	char tmp;
	if (argc < 3) {
		printf("./mycp src dest\n");	return -1;
	}
	srcfp = fopen(argv[1], "r");
	if (srcfp == NULL) {
		perror(argv[1]);	exit(-1);
	}
	destfp = fopen(argv[2], "w");
	if (destfp == NULL) {
		perror(argv[2]);	exit(-1);
	}
	while ((tmp = fgetc(srcfp)) != EOF)
		fputc(tmp, destfp);
	fclose(srcfp);	fclose(destfp);
	return 0;
}
#endif
int main(int argc, char *argv[])
{
	FILE *srcfp, *destfp;
	char tmp[1024];
	int len = 0;
	if (argc < 3) {
		printf("./mycp src dest\n");	return -1;
	}
	srcfp = fopen(argv[1], "r");
	if (srcfp == NULL) {
		perror(argv[1]);	exit(-1);
	}
	destfp = fopen(argv[2], "w");
	if (destfp == NULL) {
		perror(argv[2]);	exit(-1);
	}
	while (len = fread(tmp, 1, 1024, srcfp))
		fwrite(tmp , 1, len, destfp);
	//while (len = fread(tmp, 1024, 1, srcfp))
	//	fwrite(tmp , 1024, len, destfp);
	fclose(srcfp);	fclose(destfp);
	return 0;
}
