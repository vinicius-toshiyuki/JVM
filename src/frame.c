#include "../include/frame.h"
#include "../include/clist.h"
#include "../include/cstack.h"
#include "../include/classfile.h"
#include <stdlib.h>

frame_t * new_frame(void){
	frame_t *new = (frame_t *) malloc(sizeof(frame_t));
	new->size = 0;
	new->local_variables = new_clist();
	new->operands_stack = new_cstack();
	new->constant_pool = NULL;
	return new;
}

void destroy_frame(frame_t *f){
	free(f);
	return;
}
