#include "../include/jvm.h"
#include "../include/cstack.h"
#include "../include/celement.h"
#include "../include/method_area.h"
#include "../include/frame.h"
#include "../include/classfile.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/breads.h"
#include "../include/engine.h"

extern int JVM_ARGC;
extern char **JVM_ARGV;

jvm_t * new_jvm(void){
	jvm_t *new = (jvm_t *) calloc(1, sizeof(jvm_t));
	new->heap = new_cstack();
	new->marea = new_method_area();
	new->frame_stack = new_cstack();
	return new;
}

void start_jvm(jvm_t **_jvm, ClassFile *entry){
	jvm_t *jvm = *_jvm;
	frame_t *nf = new_frame();
	nf->constant_pool = entry->constant_pool;
	cpush(jvm->frame_stack, nf);
	frame_t *top_frame = (frame_t *) jvm->frame_stack->top->value;
	/*
	int i;
	for(i = 0; i < JVM_ARGC; i++)
		cappend(top_frame->local_variables, JVM_ARGV[i]);
	*/
	link_class(jvm->marea, entry);
	Method main = get_method_by_name(entry, "main");
	run_method(top_frame, &main);
	return;
}

