#include <stdio.h>

char *str_replace(char *str, char *substr, char *replace)
{
    char *p = strstr(str, substr);
    if (p == NULL)
        return str;
    strcpy(p, replace);
    return str;
}
int main(int argc, char *argv[])
{
    char str[] = "hello world akaedu good";
    char *substr = "world";
    char *replace = "hello";
    printf("%s\n", str_replace(str, substr, replace));
    return 0;
}