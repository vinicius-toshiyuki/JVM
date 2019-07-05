#ifndef cstack_h
#define cstack_h

#include "../include/celement.h"

typedef struct cstack_t {
	int size;
	celement_t *top;
} cstack_t;

cstack_t * new_cstack(void);
void destroy_cstack(cstack_t *);
void cpush(cstack_t *, void *);
void * cpop(cstack_t *);
#endif
