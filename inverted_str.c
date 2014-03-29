#include <stdio.h>

char *inverted_str(char *str)
{
    char *p = str;
    char *q = str;
    char tmp;
    while (*p++)
        ;
    p--;
    while (q != p) {
        tmp = *q;
        *q = *p;
        *p = tmp;
        q++;
        p--;
    }
    return str;
        
}
int main(int argc, char *argv[])
{
    char buf[] = "abcdef";
    printf("%s", inverted_str(buf));
    return 0;
}