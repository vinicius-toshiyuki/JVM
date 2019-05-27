#ifndef bfree_classfile_h
#define bfree_classfile_h

#include <stdlib.h>
#include "breads.h"

void bfree_classfile(ClassFile *class);
void bfree_attributes(attribute_info *atts, int att_count);

#endif
