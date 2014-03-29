#include <stdio.h>

typedef int (OPT*)(int , int );
int add(int a, int b)
{
    return a+b;
}
int sub(int a, int b)
{
    return a-b;
}
int mul(int a, int b)
{
    return a*b;
}
int dive(int a, int b)
{
    if (b == 0)
        exit(-1);
    return a/b;
}
OPT decide_opt(int ch)
{
    switch (ch) {
        case '+': return add;
        case '-': return sub;
        case '*': return mul;
        case '/': return dive;
        default:printf("error opt %c\n", ch); exit(-1);
    }
}
int main(int argc, char *argv[])
{
    OPT p;
    int res;
    p = decide_opt('+');
    res = p(3, 5);
    printf("res = %d\n", res);
    return 0;
}