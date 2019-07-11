#include "../include/array.h"

array_t * new_array(void){
    array_t *new = (array_t *) calloc(1, sizeof(array_t));
    new->length = 0;
    new->type = ARR_Null;
    new->items = new_clist();
    return new;
}

void array_of(array_t *array, int type, int max_length){
    array->type = type;
    array->max_length = max_length;
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