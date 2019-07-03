#ifndef jvm
#define jvm

#include "cstack.h"
#include "method_area.h"

typedef struct jvm_t {
	cstack_t *heap;
	method_area *marea;
} jvm_t;

void start_jvm(void);
void load_class(/* TODO: o que eu recebo? */);

#endif
