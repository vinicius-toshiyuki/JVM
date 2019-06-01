#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "../include/breads.h"
#include "../include/bprint_classfile.h"
#include "../include/bfree_classfile.h"
#include "../include/utils.h"
#include "../include/arguments.h"
//#include "../include/stack.h"

int verbose = 0, print_pool = 1;
char *nomearq;

int main(int argc, char **argv){
	/*Verifica os argumentos passado na execução do programa*/
	verify_arguments(argc, argv);

	nomearq = (char *) calloc(strlen(argv[1]) + 1, sizeof(char));
	strcpy(nomearq, argv[1]);
	
	/*Permite a localização do programa na lingua em que o sistema operacional esta selecionada
	  isso faz com que caracteres como 'ç' sejam exibidas no programa caso o SO esteja em pt-br*/
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











