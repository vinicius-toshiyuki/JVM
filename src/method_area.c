#include "../include/method_area.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

method_area_t * new_method_area(void){
	method_area_t *new = (method_area_t *) malloc(sizeof(method_area_t));
	new->count = 0;
	new->loaded = new_clist();
	return new;
}

void destroy_method_area(method_area_t *ma){

	return;
}

void load_class(method_area_t *marea, char *pathtoclass){
	FILE *classfile = fopen(pathtoclass, "rb");
	if(!classfile){
		fprintf(stderr, "Can not open specified file.\n");
		exit(ERR_CANTOPENFILE);
	}
	ClassFile *class = bread_classfile(classfile);
	link_class(marea, class);
	return;
}

#include <stdio.h>
void link_class(method_area_t *marea, ClassFile *class){
	cappend(marea->loaded, class);
	marea->count = marea->loaded->size;
	/* initialize_class(class); */
	return;
}
