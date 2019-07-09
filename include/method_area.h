#ifndef method_area_h
#define method_area_h

#include "classfile.h"
#include "bread_classfile.h"
#include "clist.h"
#include "../include/errcodes.h"

typedef struct method_area_t {
	int count;
	clist_t *loaded;
} method_area_t;

method_area_t * new_method_area(void);
void destroy_method_area(method_area_t *);

void load_class(method_area_t *, char *);
void link_class(method_area_t *, ClassFile *);
void initialize_class(method_area_t *, ClassFile *);

#endif
