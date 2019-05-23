#ifndef bread_constant_pool_h
#define bread_constant_pool_h

#include <stdlib.h>
#include "breads.h"

void bread_constant_pool(ClassFile *class, FILE *classfile);
void bread_constant_pool_count(ClassFile *class, FILE *classfile);
void bread_constant_pool_info(ClassFile *class, FILE *classfile);
int bread_constant_pool_tag(cp_info *cp, FILE *classfile);

/* Os tipos das variáveis __XXX são CONSTANT_XXX_info * e __classfile é FILE * */

#define bread_class_info(__Class, __classfile) \
  u2_read(__Class->name_index, __classfile);

#define bread_fieldref_info(__Fieldref, __classfile) \
{\
  u2_read(__Fieldref->class_index, __classfile); \
  u2_read(__Fieldref->name_and_type_index, __classfile); \
}

#define bread_methodref_info(__Methodref, __classfile) \
{ \
  u2_read(__Methodref->class_index, __classfile); \
  u2_read(__Methodref->name_and_type_index, __classfile); \
}

#define bread_interfacemethodref_info(__InterfaceMethodref, __classfile) \
{ \
  u2_read(__InterfaceMethodref->class_index, __classfile); \
  u2_read(__InterfaceMethodref->name_and_type_index, __classfile); \
}

#define bread_string_info(__String, __classfile) \
{ \
  u2_read(__String->string_index, __classfile); \
}

#define bread_integer_info(__Integer, __classfile) \
{ \
  u4_read(__Integer->bytes, __classfile); \
}

#define bread_float_info(__Float, __classfile) \
{ \
  u4_read(__Float->bytes, __classfile); \
}

#define bread_long_info(__Long, __classfile) \
{ \
  u4_read(__Long->high_bytes, __classfile); \
  u4_read(__Long->low_bytes, __classfile); \
}

#define bread_double_info(__Double, __classfile) \
{ \
  u4_read(__Double->high_bytes, __classfile); \
  u4_read(__Double->low_bytes, __classfile); \
}

#define bread_nameandtype_info(__NameAndType, __classfile) \
{ \
  u2_read(__NameAndType->name_index, __classfile); \
  u2_read(__NameAndType->descriptor_index, __classfile); \
}

#define bread_utf8_info(__Utf8, __classfile) \
{ \
  u2_read(__Utf8->length, __classfile); \
  __Utf8->bytes = (u1 *) malloc(sizeof(u1) * __Utf8->length); \
  for(int i = 0; i < __Utf8->length; i++) \
    u1_read((__Utf8->bytes[i]), __classfile); \
}

#endif
