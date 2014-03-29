#include <s>
#if 0
约瑟夫环问题
+ 手动创建persion文件，里面录入人的信息，姓名，年龄，性别，爱好
+ 用循环链表找到最后一个活着的人
+ 打开persion文件，读出每一个人的信息，构成一个节点，插入到双向链表里
+ 可以指定按姓名或年龄排序
+ 友善的用户界面，用户可以指定从第n个人开始，步长为m
+ 每次删除节点（被杀死的人），按顺序记录在delete.log文件里
+ 游戏有重新开始和退出选项

设计阶段：
1.数据结构
struct persion{
    char *name;
    int age;
    char sex;
    char **interest;
};
struct NODE {
    struct persion p;
    link next;
    link pre;
};
typedef struct NODE *link;
2.核心函数接口
根据文件fp里的内容创建节点，并插入到head的环形链表里
link josephson_init(FILE *fp, link *head);
游戏从指定的第n个人开始，步长为m，数到的节点删除，直到剩一个节点为止，游戏结束，返回最后一个节点地址
link josephson_game(link *head, int n, int m);
删除的节点写到log文件里，方便观察和调试，写文本文件
void delete_world_log(FILE *fp, link p);
把加载好的链表以二进制的形式写到文件persion.bin
void josephson_write_bin(FILE *fp, link *head);
加载二进制文件persion.bin文件里的数据到链表里
void josephson_read_bin(FILE *fp, link *head);

链表相关操作
void circle_init(link *head);
void circle_destroy(link *head);
link make_node(char *str);
void insert_node(link *head, link p);
void delete_node(link p);
void sort_by_name(link *head);
void sort_by_age(link *head);
上述两个排序函数可以采用泛性函数思想实现为
void sort_node(link *head, int (*cmp_node)(link a, link b));

#endif

struct persion{
    char *name;
    int age;
    char sex;
    char **interest;
};
struct NODE {
    struct persion p;
    link next;
    link pre;
};
typedef struct NODE *link;
link josephson_init(FILE *fp, link *head);
link josephson_game(link *head, int n, int m);
void delete_world_log(FILE *fp, link p);
void josephson_write_bin(FILE *fp, link *head);
void josephson_read_bin(FILE *fp, link *head);
void circle_init(link *head);
void circle_destroy(link *head);
link make_node(char *str);
void insert_node(link *head, link p);
void delete_node(link p);
void show_node(link p);
void sort_by_name(link *head);
void sort_by_age(link *head);
void sort_node(link *head, int (*cmp_node)(link a, link b));
void recieve_n_m(int *n, int *m)
{
    char buf[32];
    printf("Please input N persion\n");
    fgets(buf, sizeof(buf), stdin);
    *n = atoi(strtok(buf, "\n"));
    printf("Please input M step\n");
    fgets(buf, sizeof(buf), stdin);
    *m = atoi(strtok(buf, "\n"));
}

void select_sort_link(link *head)
{
        printf("1. sort link by name\n"
            "2. sort link by age\n"
            "3. default\n");
}
void recieve_n_m(int *n, int *m)
{

}
int play_again(void)
{
    char buf[100];
    printf("play again Y or N\n");
    fgets(buf, sizeof(buf), stdin);
    if (strcmp("Y\n", buf))
        return 1;
    else
        return 0;
}
int main(int argc, char *argv[])
{
    FILE *fp, *fp_bin;
    link head;
    if (argc < 2) {
        printf("./a.out persion");
        exit(-1);
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(-1);
    }
    if ((fp_bin = fopen("persion.bin", "w")) == NULL) {
        perror("persion.bin");
        exit(-1);
    }
    circle_init(&head);
    josephson_init(fp, &head);
    fclose(fp);
    josephson_write_bin(fp_bin, &head);
    rewind(fp_bin);
    while (1) {
        link p;
        int n, m;
        select_sort_link(&head);
        recieve_n_m(&n, &m);
        p = josephson_game(&head, n, m);
        printf("the lucky man is \n");
        show_node(p);
        circle_destroy(&head);
        if (play_again())
            josephson_read_bin(fp_bin, &head);
        else
            break;
    }
    fclose(fp_bin);
    return 0;
}