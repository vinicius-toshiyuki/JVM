#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "../include/breads.h"
#include "../include/bprint_classfile.h"
#include "../include/bfree_classfile.h"
//#include "../include/stack.h"

int comp(const void *a, const void *b){return *((char *) a) - *((char *) b);}

int verbose = 0, print_pool;

int main(int argc, char **argv){
	if(argc < 2){
		fprintf(stderr, "Usage:\n\t%s <.class file name>\n", argv[0]);
		exit(ERR_NOFILE);
	}

	if(argc == 3){
		char opt[] = "vc";
		char *options = *(argv + 2);
		qsort(options, strlen(options), sizeof(char), comp);
		if(bsearch(&opt[0], options, strlen(options), sizeof(char), comp)) verbose = 1;
		if(bsearch(&opt[1], options, strlen(options), sizeof(char), comp)) print_pool = 1;
	}

	setlocale(LC_ALL, "");
	char *filename = argv[1];
	FILE *classfile = fopen(filename, "rb");

	if(classfile == NULL){
		fprintf(stderr, "Failed to open specified file\n");
		exit(ERR_CANTOPENFILE);
	}

	if(verbose) printf("File opened\n");
	
	ClassFile *class = bread_classfile(classfile);

	if(verbose) printf("File read\n");

	bprint_classfile(class);

	bfree_classfile(class);

	fclose(classfile);

	return 0;
}











