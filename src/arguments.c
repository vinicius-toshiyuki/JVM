#include "../include/arguments.h"

extern int verbose, print_pool;

void verify_arguments(int argc, char **argv) {
    if(argc < 2){
		fprintf(stderr, "Usage:\n\t%s <.class file name>\n", argv[0]);
		exit(ERR_NOFILE);
	}

    if(argc >= 3){
		/*Opções de argumentos possíveis*/
		char opt[] = "vc";
		/*options recebe os argumentos passados na execução*/
		char *options = *(argv + 2);
		/*Realiza um quick sort na string dos argumentos*/
		qsort(options, strlen(options), sizeof(char), comp);
		if(bsearch(&opt[0], options, strlen(options), sizeof(char), comp)) verbose = 1;
		if(bsearch(&opt[1], options, strlen(options), sizeof(char), comp)) print_pool = 0;
	}
	return;
}