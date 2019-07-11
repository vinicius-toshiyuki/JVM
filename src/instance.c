#include "../include/instance.h"

instance_t * new_instance(void){
    instance_t *new = (instance_t *) calloc(1, sizeof(instance_t));
    new->class = NULL;
    new->variables = NULL;
    return new;
}

void destroy_instance(instance_t *instance){
    destroy_clist(instance->variables);
    free(instance);
    instance = NULL;
}

void instantiate_by_name(instance_t *instance, method_area_t *marea, char *classname, clist_t *variables){
    instance->class = get_class_by_name(marea, classname);
    instance->variables = variables;
}

void instantiate_by_index(instance_t *instance, jvm_t *jvm, u2 cp_index, clist_t *variables){
    info_t *classname_utf8 = get_constant_pool_entry(jvm->frame_stack->top->value, cp_index);
    char *classname = (char *) calloc(classname_utf8->Utf8.length + 1, sizeof(char));
    memcpy(classname, classname_utf8->Utf8.bytes, classname_utf8->Utf8.length);
    ClassFile *class = get_class_by_name(jvm->marea, classname);
    free(classname);
    instance->class = class;
    instance->variables = variables;
}

#include <stdio.h>
char * get_class_name(instance_t *instance){
	ClassFile *class = instance->class;
	info_t *classname_class = class->constant_pool[class->this_class - 1].info;
    info_t *classname_utf8 = class->constant_pool[classname_class->Class.name_index - 1].info;
	char *classname = (char *) calloc(classname_utf8->Utf8.length + 1, sizeof(char));
	memcpy(classname, classname_utf8->Utf8.bytes, classname_utf8->Utf8.length);
	return classname;
}
