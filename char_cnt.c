#include <stdio.h>

int char_cnt(char *str, int ch)
{
    int n = 0;
    while (*str) {
        if (*str == ch)
            n++;
        str++;
    }
    return n;
}
int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("./a.out str key");
        exit(-1);
    }
    printf("%c : %d\n", *argv[2], char_cnt(argv[1], *argv[2]));
    return 0;
}