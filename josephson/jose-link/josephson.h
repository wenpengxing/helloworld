#ifndef JOSEPHSON_H_
#define JOSEPHSON_H_
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
link josephson_init(FILE *fp, link *head);
link josephson_game(link *head, int n, int m);
void delete_word_log(FILE *fp, link p);
void josephson_write_bin(FILE *fp, link *head);
void josephson_read_bin(FILE *fp, link *head);
void write_bin(FILE *fp, link p);
void circle_init(link *head);
void circle_destroy(link *head);
link make_node(char *buf);
void insert_node(link *head, link p);
void delete_node(link *head, link p);
void show_node(link p);
void sort_by_name(link *head);
void sort_by_age(link *head);
int cmp_name(link a, link b);
int cmp_age(link a, link b);
void sort_node(link *head, int (*cmp_node)(link a, link b));
void select_sort_link(link *head);
void recieve_n_m(int *n, int *m);
int play_again(void);
void travel_node(link *head);
FILE *FOPEN(char *path, char *mode);
#endif
