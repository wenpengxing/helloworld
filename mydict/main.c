#include "common.h"

int main(int argc, char *argv[])
{
	dict_t dict, *usr = NULL; 
	ditem_t *item; int i;
	char buf[BUF_SIZE];
	
	if(argc <= 1)
		wrong_command();

	if(strcmp(argv[1], "-index") == 0){
		if(create_idx("dict.txt", "dict.dat") == FALSE)
			err_sys("fail to create index");
		else
			return 0;
	}else if(strncmp(argv[1], "-text", 5) == 0 ){

		if(dict_init_txt("dict.txt", &dict) == NULL)
			err_sys("fail to dict_init");

	}else if(strncmp(argv[1], "-bin", 4) == 0){

		if(dict_init_bin("dict.dat", &dict) == NULL)
			err_sys("fail to doct_init");
	}else
		wrong_command();

	if(argc == 4 && strncmp("-f", argv[2], 2) == 0){
		usr = (dict_t *)malloc(sizeof(dict_t));
		if(usr == NULL){
			dict_free(&dict);
			err_sys("fail to init usr data");
		}
		if(dict_init_txt(argv[3], usr) == NULL){
			dict_free(&dict);
			err_sys("fail to init usr data");
		}
	}
	combine_sort(dict.dict,0,dict.nword - 1);
	if(usr)combine_sort(usr->dict,0,usr->nword -1);

	DEBUG_PRINT0("init done...\n");

	while(fgets(buf, BUF_SIZE, stdin)){
		if(buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		if(strcmp(buf, "exit") == 0)
			break;
		item = dict_search(buf, &dict);
		
		if(item == NULL && usr != NULL)
			item = dict_search(buf, usr);

		if(item == NULL)
			printf("not found...\n");
		else{
			printf("%s :\n", item->key_word);
			for(i = 0; i < item->trans_num; i++)
				printf("trans %d: %s\n", i + 1, item->trans[i]);
		}
		printf("\n");
	}

	dict_free(&dict);
	if(usr != NULL){
		dict_free(usr);
		free(usr);
	}

	return 0;
}	
