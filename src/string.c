#include "../include/string.h"
#include <stdlib.h>

String * new_string(void){
	String *new = (String *) calloc(1, sizeof(String));
	new->tag = STR_Null;
	new->data = NULL;
	return new;
}

void string_of(String *str, int tag, void *data){
	str->tag = tag;
	str->data = data;
}
