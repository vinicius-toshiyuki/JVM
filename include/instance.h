/**
 * @file instance.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of an instance of a object.
 */
#ifndef instance_h
#define instace_h

#include "classfile.h"
#include "clist.h"
#include "jvm.h"
#include "method_area.h"
#include "constant_pool.h"
#include <stdlib.h>

/**
 * \struct instance_t
 * Struct of an object instance.
 */
typedef struct instance_t {
    ClassFile *class;
    clist_t *variables;
} instance_t;

/**
 *  Create new object with null values.
 */
instance_t * new_instance(void);

/**
 *  Destroy object
 */
void destroy_instance(instance_t *instance);

/**
 *  Initialize object class from class classname in jvm method area marea and instance fields.
 */
void instantiate_by_name(instance_t *instance, method_area_t *marea, char *classname, clist_t *variables);

/**
 *  Initialize object class from class in jvm_t jvm top frame constant pool at index class_index and instance fields.
 */
void instantiate_by_index(instance_t *instance, jvm_t *jvm, u2 class_index, clist_t *variables);

/**
 *  Get an instance class name.
 */
char * get_class_name(instance_t *instance);

/**
 *  Get a method of an instance.
 */
method_info * get_method_info_by_name(instance_t *instance, char *method_name);

#endif /* instance_h */
