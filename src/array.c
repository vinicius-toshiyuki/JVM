#include "../include/array.h"
#include <stdio.h>
#include "../include/errcodes.h"
#include <string.h>

array_t * new_array(void){
    array_t *new = (array_t *) calloc(1, sizeof(array_t));
    new->length = 0;
    new->tag = ARR_Null;
		new->class_name = NULL;
    new->items = new_clist();
    return new;
}

void array_of(array_t *array, int tag, int max_length){
    array->tag = tag;
    array->max_length = max_length;
}

void array_of_class(array_t *array, char *class_name){
	if(array->tag != ARR_RefClass){
		fprintf(stderr, "Invalid array to initilize class name\n");
		exit(ERR_INVARR);
	}
	array->class_name = (char *) calloc(strlen(class_name) + 1, sizeof(char));
	strcat(array->class_name, class_name);
}

void destroy_array(array_t *array){
    destroy_clist(array->items);
    free(array);
}

void * at(array_t *array, int index){
    if(index <= array->length && index >= 0 && array->length)
        return cat(array->items, index);
    return NULL;
}

void put(array_t *array, int index, void *value){
    if(index > array->length || index < 0 || array->length == array->max_length)
        return;
    cinsert(array->items, index, value);
    array->length = array->items->size;
}

void * get(array_t *array, int index){
    if(index > array->length || index < 0 || !array->length)
        return NULL;
    array->length--;
    return cremove(array->items, index);
}
