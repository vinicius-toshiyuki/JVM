#include "../include/jvm.h"
#include "../include/cstack.h"
#include "../include/celement.h"
#include "../include/method_area.h"
#include "../include/frame.h"
#include "../include/classfile.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/breads.h"

extern int JVM_ARGC;
extern char **JVM_ARGV;

jvm_t * new_jvm(void){
	jvm_t *new = (jvm_t *) malloc(sizeof(jvm_t));
	new->heap = new_cstack();
	new->marea = new_method_area();
	new->frame_stack = new_cstack();
	return new;
}

void start_jvm(jvm_t **_jvm, ClassFile *entry){
	jvm_t *jvm = *_jvm;
	cpush(jvm->frame_stack, new_frame());
	frame *top_frame = (frame *) jvm->frame_stack->top->value;
	int i;
	for(i = 0; i < JVM_ARGC; i++)
		cappend(top_frame->local_variables, JVM_ARGV[i]);
	return;
}

void load_class(char *pathtoclass, jvm_t *jvm){
	FILE *classfile = fopen(pathtoclass, "rb");
	if(!classfile){
		fprintf(stderr, "Can not open specified file.\n");
		exit(ERR_CANTOPENFILE);
	}
	ClassFile *class = bread_classfile(classfile);
	link_class(class, jvm->marea);
	return;
}
