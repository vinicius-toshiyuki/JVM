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
	new->pc = NULL;
	return new;
}

#include <stdio.h>
void destroy_frame(frame_t *f){
	destroy_clist(f->local_variables);
	destroy_cstack(f->operands_stack);
	free(f);
	return;
}
