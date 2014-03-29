#include <stdio.h>

int word_cnt(FILE *fp)
{
    char buf[1024];
    int n = 0;
    char *save = buf;
    while (fgets(buf, sizeof(buf), fp)) {
        while (strtok_r(save, " ,.;\n", &save))
            n++;
    }
    return n;
}
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    int n;
    if (fp == NULL) {
        perror(argv[1]);
        exit(-1);
    }
    n = word_cnt(fp);
    printf("%d\n", n);
    fclose(fp);
    return 0;
}