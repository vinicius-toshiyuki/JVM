#ifndef bread_interfaces_h
#define bread_interfaces_h

#include <stdlib.h>
#include "breads.h"

void bread_interfaces(ClassFile *class, FILE *classfile);

#define bread_interfaces_count(__class, __classfile) u2_read(__class->interfaces_count, __classfile)

#endif
