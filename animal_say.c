#include <stdio.h>
#include <string.h>
struct animal {
	char name[20];
	void (*say_what)(void);
	int level;
};
typedef struct animal ANIMAL;
void cow_say(void)
{
	printf("men men\n");
}
void dog_say(void)
{
	printf("wang wang\n");
}
void man_say(void)
{
	printf("OH YEAH\n");
}
void init_animal(char *name, void (*say)(void), int level, ANIMAL *p)
{
	strcpy(p->name, name);
	p->say_what = say;
	p->level = level;
}
int level_cmp(ANIMAL a, ANIMAL b)
{
	if (a.level < b.level)
		return 1;
	else if (a.level == b.level)
		return 0;
	else
		return -1;
}
int name_cmp(ANIMAL a, ANIMAL b)
{
	return strcmp(a.name, b.name);
}
void swap(ANIMAL *a, ANIMAL *b)
{
	ANIMAL tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void show_animal(ANIMAL *a, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%s\tsay\t", a[i].name);
		a[i].say_what();
	}
}
void sort_animal(ANIMAL *a, int n, int (*cmp)(ANIMAL, ANIMAL))
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n-i-1; j++)
			if (cmp(a[j], a[j+1]) > 0)
				swap(&a[j], &a[j+1]);
}
int main(void)
{
	ANIMAL a[10];

	init_animal("cow", cow_say, 2, &a[0]);
	init_animal("dog", dog_say, 1, &a[1]);
	init_animal("man", man_say, 3, &a[2]);
	sort_animal(a, 3, level_cmp);
	show_animal(a, 3);
	printf("**************\n");
	sort_animal(a, 3, name_cmp);
	show_animal(a, 3);
	return 0;
}
