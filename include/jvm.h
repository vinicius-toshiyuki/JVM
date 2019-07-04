#ifndef jvm_h
#define jvm_h

#include "cstack.h"
#include "method_area.h"

typedef struct jvm_t {
	cstack_t *heap;
	method_area_t *marea;
} jvm_t;

void start_jvm(jvm_t **);
void load_class(char *pathtoclass, jvm_t *jvm);

#endif
