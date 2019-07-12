#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "../include/breads.h"
#include "../include/bprint_classfile.h"
#include "../include/bfree_classfile.h"
#include "../include/utils.h"
#include "../include/initialize.h"
#include "../include/jvm.h"

extern char *CLASSFILE;
extern int MODE;
extern int VERBOSE;
extern int SECRET;

int main(int argc, char **argv){
	initialize(argc, argv);
	
	setlocale(LC_ALL, ""); /* Allows the location of the program in the language in which the operating system is selected so that characters like 'ç' are displayed in the program if the OS is in portuguese */
	char *filename = CLASSFILE;
	FILE *classfile = fopen(filename, "rb");
	if(classfile == NULL){
		fprintf(stderr, "Failed to open specified file\n");
		exit(ERR_CANTOPENFILE);
	}
	if(VERBOSE) printf("File opened\n");

	ClassFile *class = bread_classfile(classfile, filename);
	if(VERBOSE) printf("File read\n");

	if(MODE == OPTION_viewer){
		bprint_classfile(class);
		bfree_classfile(class);
		fclose(classfile);
	}else if(MODE == OPTION_interpreter){
		jvm_t *jvm = new_jvm();
		start_jvm(&jvm, class);
		if(SECRET)
			printf("Mainnnnnnnn\n");
	}

	return 0;
}











