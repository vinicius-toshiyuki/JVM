/**
 * @file bread_this_class.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_this_class_h
#define bread_this_class_h

#include <stdlib.h>
#include "breads.h"

#define bread_this_class(__class, __classfile) u2_read(__class->this_class, __classfile)

#endif
