#include "../include/object.h"

object_t * new_object(void){
    object_t *new = (object_t *) calloc(1, sizeof(object_t));
    new->class = NULL;
    new->instance_variables = NULL;
    return new;
}

void destroy_object(object_t *object){
    destroy_clist(object->instance_variables);
    free(object);
    object = NULL;
}

void instantiate_by_name(object_t *object, method_area_t *marea, char *classname, clist_t *instance_variables){
    object->class = get_class_by_name(marea, classname);
    object->instance_variables = instance_variables;
}

void instantiate_by_index(object_t *object, jvm_t *jvm, u2 cp_index, clist_t *instance_variables){
    info_t *classname_utf8 = get_constant_pool_entry(jvm->frame_stack->top->value, cp_index);
    char *classname = (char *) calloc(classname_utf8->Utf8.length + 1, sizeof(char));
    memcpy(classname, classname_utf8->Utf8.bytes, classname_utf8->Utf8.length);
    ClassFile *class = get_class_by_name(jvm->marea, classname);
    free(classname);
    object->class = class;
    object->instance_variables = instance_variables;
}