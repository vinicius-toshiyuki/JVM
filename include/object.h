#ifndef object_h
#define object_h

#include "classfile.h"
#include "clist.h"
#include "jvm.h"
#include "method_area.h"
#include "constant_pool.h"
#include <stdlib.h>

typedef struct object_t {
    ClassFile *class;
    clist_t *instance_variables;
} object_t;

/**
 *  Create new object_t with null values
 */
object_t * new_object(void);

/**
 *  Destroy object_t
 */
void destroy_object(object_t *object);

/**
 *  Initialize object_t class from class classname in jvm method area marea and instance fields
 */
void instantiate_by_name(object_t *object, method_area_t *marea, char *classname, clist_t *instance_variables);

/**
 *  Initialize object_t class from class in jvm_t jvm top frame constant poll at index class_index and instance fields
 */
void instantiate_by_index(object_t *object, jvm_t *jvm, u2 class_index, clist_t *instance_variables);


#endif
