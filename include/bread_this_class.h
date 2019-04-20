#ifndef bread_this_class_h
#define bread_this_class_h

#include <stdlib.h>
#include "breads.h"

#define bread_this_class(__class, __classfile) u2_read(__class->this_class, __classfile)

#endif
