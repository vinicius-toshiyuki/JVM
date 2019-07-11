#ifndef instance_h
#define instace_h

#include "classfile.h"
#include "clist.h"
#include "jvm.h"
#include "method_area.h"
#include "constant_pool.h"
#include <stdlib.h>

typedef struct instance_t {
    ClassFile *class;
    clist_t *variables;
} instance_t;

/**
 *  Create new object_t with null values
 */
instance_t * new_instance(void);

/**
 *  Destroy object_t
 */
void destroy_instance(instance_t *instance);

/**
 *  Initialize object_t class from class classname in jvm method area marea and instance fields
 */
void instantiate_by_name(instance_t *instance, method_area_t *marea, char *classname, clist_t *variables);

/**
 *  Initialize object_t class from class in jvm_t jvm top frame constant poll at index class_index and instance fields
 */
void instantiate_by_index(instance_t *instance, jvm_t *jvm, u2 class_index, clist_t *variables);


#endif
