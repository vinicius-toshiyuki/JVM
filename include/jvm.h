#ifndef jvm
#define jvm

#include "cstack.h"

typedef struct jvm {
	cstack_t *heap;
	method_area *marea;
} jvm;

#endif
