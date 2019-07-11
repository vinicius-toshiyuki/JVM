#include "../include/objectref.h"
#include <stdlib.h>

objectref_t * new_objectref(void){
    objectref_t *new = (objectref_t *) calloc(1, sizeof(objectref_t));
    new->tag = -1;
    new->object = NULL;
    return new;
}

void destroy_objectref(objectref_t *ref){
    free(ref);
}

void reference_of(objectref_t *ref, int type, void *refvalue){
    ref->tag = type;
    ref->object = refvalue;
}