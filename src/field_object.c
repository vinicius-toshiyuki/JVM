#include "../include/field_object.h"
#include <stdlib.h>

field_object_t * new_field_object(void){
	field_object_t *new = (field_object_t *) calloc(1, sizeof(field_object_t));
	new->ref = NULL;
	new->tag = FIELD_Null;
	return new;
}

void destroy_field_object(field_object_t *field_object){
	free(field_object);
}
