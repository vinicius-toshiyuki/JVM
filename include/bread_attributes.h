#ifndef bread_attributes_h
#define bread_attributes_h

#include "breads.h"
#include <string.h>

void bread_attributes(attribute_info *atts, int atts_count, FILE *classfile, ClassFile *);
void bread_att_info(u1 *, int, ClassFile);

#define bread_attributes_count(__class, __classfile) \
{ \
  u2_read(__class->attributes_count, __classfile); \
  __class->attributes = (attribute_info *) malloc(sizeof(attribute_info) * __class->attributes_count); \
}

#endif
