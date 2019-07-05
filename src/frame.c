#include "../include/frame.h"
#include "../include/clist.h"
#include "../include/cstack.h"
#include <stdlib.h>

frame * new_frame(void){
	frame *new = (frame *) malloc(sizeof(frame));
	new->size = 0;
	new->local_variables = new_clist();
	new->operands_stack = new_cstack();
	return new;
}

void destroy_frame(frame *f){
	free(f);
	return;
}
