/**
 * @file method_area.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the definition of the method area.
 */
#ifndef method_area_h
#define method_area_h

#include "classfile.h"
#include "bread_classfile.h"
#include "clist.h"
#include "../include/errcodes.h"

/**
 * \struct method_area_t
 * Struct of the method area.
 */
typedef struct method_area_t {
	int count;
	clist_t *loaded;
} method_area_t;

/**
 * Create a method area.
 */
method_area_t * new_method_area(void);

/**
 * Destroy the passed method area.
 */
void destroy_method_area(method_area_t *);

/**
 * Load an class into the method area by name.
 */
void load_class(method_area_t *, char *);

/**
 * Link an class into the method area.
 */
void link_class(method_area_t *, ClassFile *);

/**
 * Initialize the passed class from method area.
 */
void initialize_class(method_area_t *, ClassFile *);

/**
 * Verify if the class is loaded into the method area.
 */
int is_loaded(method_area_t *, char *);

/**
 *	Get a class @classname in method area @marea.
 */
ClassFile * get_class_by_name(method_area_t *marea, char *classname);

#endif
