#ifndef frame_h
#define frame_h

#include "clist.h"
#include "cstack.h"
#include "classfile.h"

typedef struct frame_t {
	int size;
	clist_t *local_variables;
	cstack_t *operands_stack;
	cp_info *constant_pool;
} frame_t;

frame_t * new_frame(void);
void destroy_frame(frame_t *);

#endif
