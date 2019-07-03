#include "../include/method_area.h"
#include <stdlib.h>

method_area * new_method_area(void){
	method_area *new = (method_area *) malloc(sizeof(method_area));
	new->count = 0;
	new->cpools = NULL;
	return new;
}

void destroy_method_area(method_area *ma){

	return;
}
