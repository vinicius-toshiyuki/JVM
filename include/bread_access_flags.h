#ifndef bread_access_flags_h
#define bread_access_flags_h

#include <stdlib.h>
#include "breads.h"

#define bread_access_flags(__class, __classfile) u2_read(__class->access_flags, __classfile)

#endif
