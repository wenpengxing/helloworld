#include <stdio.h>
int  cut_bit(int num, int begin, int end) //begin=2 end=5
{
	int i;
	int mask = 0;
	if (begin >= end)
		return 0;
	for (i = begin; i <= end; i++)
		mask = (mask<<1) | 1;
	mask <<= begin;
	return mask & num;
}
void show_num_bit(int num)
{
	int i;
	for (i = 0; i < 32; i++)
		printf("%d ", (num >> (31-i)) & 0x1);
	putchar('\n');
}
int main(void)
{
	int num = 0x55; //0000 0101  0101
	int res;
	res = cut_bit(num, 2, 5);
	show_num_bit(res);
	return 0;
}
