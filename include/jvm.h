#ifndef jvm_h
#define jvm_h

#include "cstack.h"
#include "method_area.h"
#include "classfile.h"

typedef struct jvm_t {
	cstack_t *heap;
	method_area_t *marea;
	cstack_t *frame_stack;
} jvm_t;

jvm_t * new_jvm(void);
void start_jvm(jvm_t **, ClassFile *);

#endif
