#ifndef method_area_h
#define method_area_h

#include "classfile.h"

typedef struct method_area_t {
	int count;
	ClassFile **loaded;
} method_area_t;

method_area_t * new_method_area(void);
void destroy_method_area(method_area_t *);
void link_class(ClassFile *class, method_area_t *marea);

#endif
