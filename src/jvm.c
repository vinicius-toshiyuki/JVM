#include "../include/jvm.h"
#include "../include/cstack.h"
#include "../include/method_area.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/breads.h"

void start_jvm(jvm_t **jvm){
	*jvm = (jvm_t *) malloc(sizeof(jvm_t));
	(*jvm)->heap = new_cstack();
	(*jvm)->marea = new_method_area();
	return;
}

void load_class(char *pathtoclass, jvm_t *jvm){
	FILE *classfile = fopen(pathtoclass, "rb");
	if(!classfile){
		fprintf(stderr, "Can not open specified file.\n");
		exit(ERR_CANTOPENFILE);
	}
	ClassFile *class = bread_classfile(classfile);
	link_class(class, jvm->marea);
	return;
}
