#include "../include/method_area.h"
#include "../include/classfile.h"
#include <string.h>
#include <stdlib.h>

method_area_t * new_method_area(void){
	method_area_t *new = (method_area_t *) malloc(sizeof(method_area_t));
	new->count = 0;
	new->loaded = NULL;
	return new;
}

void destroy_method_area(method_area_t *ma){

	return;
}

#include <stdio.h>
void link_class(ClassFile *class, method_area_t *marea){
	ClassFile **aux = (ClassFile **) malloc(sizeof(ClassFile) * ++marea->count);
	memcpy(aux, marea->loaded, sizeof(ClassFile *) * (marea->count - 1));
	free(marea->loaded);
	marea->loaded = aux;
	marea->loaded[marea->count - 1] = class;
	/*initialize_class(class);*/
	return;
}
