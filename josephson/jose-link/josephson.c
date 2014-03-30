#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "josephson.h"
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
/*
struct persion{
	char *name;
	int age;
	char sex;
	int n_insterest;
	char **insterest;
};
typedef struct NODE *link;
struct NODE {
	struct persion man;
	link next;
	link pre;
};
*/
link josephson_init(FILE *fp, link *head)
{
	char buf[1024];
	link p;
	while (fgets(buf, sizeof(buf), fp)) {
		p = make_node(buf);
		insert_node(head, p);
	}
}
link josephson_game(link *head, int n, int m)
{
	int i;
	static int num = 0;
	link p = *head, q;
	for (i = 1; i < n; i++)
		p = p->next;
	while ((*head)->next != (*head)->pre) {
		for (i = 1; i < m; i++) 
			p = p->next;

		q=p->next;
		printf("delete **********   %d\n", num++);
		show_node(p);
		delete_node(head, p);
		p = q;
	}
	return *head;
}
void delete_word_log(FILE *fp, link p)
{
}
void write_bin(FILE *fp, link p)
{
	int len, i;
	len = strlen(p->man.name)+1;
	fwrite(&len, sizeof(int), 1, fp);
	fwrite(p->man.name, sizeof(char), len, fp);
	fwrite(&p->man.age, sizeof(int), 1, fp);
	fwrite(&p->man.sex, sizeof(char), 1, fp);
	fwrite(&p->man.n_insterest, sizeof(int), 1, fp);
	for (i = 0; i < p->man.n_insterest; i++) {
		len = strlen(p->man.insterest[i])+1;
		fwrite(&len, sizeof(int), 1, fp);
		fwrite(p->man.insterest[i], sizeof(char), len, fp);
	}
}
/*
 *  manynode|namelen|name|age|sex|n_interest|first_interestlen|first_interest|...
 */
void josephson_write_bin(FILE *fp, link *head)
{
	link p = *head;
	link q = *head;
	int manynode = 1;
	while (q->next != *head) {
		q = q->next;
		manynode++;
	}
	printf("manynode %d\n", manynode);
	fwrite(&manynode, sizeof(int), 1, fp);
	write_bin(fp, p);
	p = p->next;
	while (p != *head) {
		write_bin(fp, p);
		p = p->next;
	}
}
void josephson_read_bin(FILE *fp, link *head)
{
	int namelen, manynode, i, j, n_insterest, insterestlen;
	char buf[1024];
	link p;
	fread(&manynode, sizeof(int), 1, fp);
	for (i = 0; i < manynode; i++) {
		p = make_node(NULL);
		fread(&namelen, sizeof(int), 1, fp);
		p->man.name = malloc(namelen);
		fread(p->man.name, sizeof(char), namelen, fp);

		fread(&p->man.age, sizeof(int), 1, fp);
		fread(&p->man.sex, sizeof(char), 1, fp);

		fread(&p->man.n_insterest, sizeof(int), 1, fp);
		p->man.insterest = malloc(p->man.n_insterest * sizeof(char *));
		for (j = 0; j < p->man.n_insterest; j++) {
			fread(&insterestlen, sizeof(int), 1, fp);
			p->man.insterest[j] = malloc(insterestlen);
			fread(p->man.insterest[j], sizeof(char), insterestlen, fp);
		}
		insert_node(head, p);
	}

}
void circle_init(link *head)
{
	*head = NULL;
}
void circle_destroy(link *head)
{
	link p = *head, q;
	while (p->next != p->pre){
		q = p->next;
		delete_node(head, p);
		p = q;
	}
	delete_node(head, p);
	*head = NULL;
}
link make_node(char *buf)
{
	link p = malloc(sizeof*p);
	char *tmp, *s;
	int len, m, j;

	if (buf == NULL) {
		p->man.name = NULL;
		p->man.age = 0;
		p->man.sex = '\0';
		p->man.n_insterest = 0;
		p->man.insterest = NULL;
		p->next = p;
		p->pre = p;
		return p;
	}

	//data init
	tmp = strtok(buf, " \t");
	len = strlen(tmp);
	p->man.name = malloc(len+1);
	strcpy(p->man.name, tmp);
	p->man.age = atoi(strtok(NULL, " \t"));
	tmp = strtok(NULL, " \t");
	p->man.sex = *tmp;
	tmp = strtok(NULL, " \t\n"); // run@football
	m = 1;
	s = tmp;
	while ((s = strchr(s, '@'))) {
		m++;
		s++;
	}
	p->man.n_insterest = m;
	p->man.insterest = malloc(p->man.n_insterest*sizeof(char *));
	j = 0;
	while ((s = strtok_r(tmp, "@", &tmp)) && (j < p->man.n_insterest)) {
		p->man.insterest[j] = malloc(strlen(s)+1);
		strcpy(p->man.insterest[j], s);
		j++;
	}
	// point init
	p->next = p;
	p->pre = p;
	return p;
}
void insert_node(link *head, link p)
{
	if (*head == NULL) {
		*head = p;
		return;
	}
	p->next = *head;
	p->pre = (*head)->pre;
	(*head)->pre->next = p;
	(*head)->pre = p;
}
void delete_node(link *head, link p)
{
	if (*head == p)
		*head = p->next;
	p->next->pre = p->pre;
	p->pre->next = p->next;
}
void show_node(link p)
{
	int j;
		printf("%s\t%d\t%c\t%d\t", p->man.name, p->man.age, p->man.sex, p->man.n_insterest);
		for (j = 0; j < p->man.n_insterest; j++)
			printf("%s\t", p->man.insterest[j]);
		printf("\n");
}
/*
void sort_by_name(link *head)
{
}
void sort_by_age(link *head)
{
}
*/
int cmp_name(link a, link b)
{
	return strcmp(a->man.name, b->man.name);
}
int cmp_age(link a, link b)
{
	return a->man.age - b->man.age;
}
void sort_node(link *head, int (*cmp_node)(link a, link b))
{
}
void travel_node(link *head)
{
	int i = 1;
	link p = *head, q;
		printf("%d******\n",i++);
		show_node(p);
		p = p->next;
	while (p != *head) {
		printf("%d******\n",i++);
		show_node(p);
		p = p->next;
	}
}
void select_sort_link(link *head)
{
	char buf[100];
	printf("1. sort link by name\n"
			"2. sort link by age\n"
			"3. default\n");
	switch (atoi(gets(buf))) {
		case 1: sort_node(head, cmp_name); break;
		case 2: sort_node(head, cmp_age); break;
		case 3:
		default: return;
	}
	return;
}
void recieve_n_m(int *n, int *m)
{
	char buf[100];
	printf("game begin from which persion:\n");
	*n = atoi(gets(buf));
	printf("m step:\n");
	*m = atoi(gets(buf));
}
int play_again(void)
{
	char buf[100];
	printf("play again Y or N\n");
	fgets(buf, sizeof(buf), stdin);
	if (strcmp("Y\n", buf) == 0)
		return 1;
	else
		return 0;
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

int main(int argc, char *argv[])
{
	FILE *fp, *fp_bin;
	link head;
	if (argc < 2) {
		printf("./a.out persion\n");
		exit(-1);
	}
	fp = FOPEN(argv[1], "r");
	fp_bin = FOPEN("persion.bin", "w");

	circle_init(&head);
	josephson_init(fp, &head);
	fclose(fp);
	josephson_write_bin(fp_bin, &head);
	fflush(fp_bin);
	fclose(fp_bin);
	while (1) {
		link p;
		int n, m;
		select_sort_link(&head);
		travel_node(&head);
		recieve_n_m(&n, &m);
		p = josephson_game(&head, n, m);
		printf("the lucky man is \n");
		show_node(p);
		circle_destroy(&head);
		if (play_again()) {
			circle_init(&head);
			fp_bin = FOPEN("persion.bin", "r");
			josephson_read_bin(fp_bin, &head);
			fclose(fp_bin);
		}
		else
			break;
	}
	return 0;
}
