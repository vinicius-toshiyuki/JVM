#ifndef frame_h
#define frame_h

#include "clist.h"
#include "cstack.h"

typedef struct frame {
	int size;
	clist_t *local_variables;
	cstack_t *operands_stack;
} frame;

frame * new_frame(void);
void destroy_frame(frame *);

#endif
