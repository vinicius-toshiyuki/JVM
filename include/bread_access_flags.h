/**
 * @file bread_access_flags.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_access_flags_h
#define bread_access_flags_h

#include <stdlib.h>
#include "breads.h"

#define bread_access_flags(__class, __classfile) u2_read(__class->access_flags, __classfile)

#endif
