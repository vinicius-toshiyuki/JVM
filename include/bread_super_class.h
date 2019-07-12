/**
 * @file bread_super_class.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_super_class_h
#define bread_super_class_h

#include <stdlib.h>
#include "breads.h"

#define bread_super_class(__class, __classfile) u2_read(__class->super_class, __classfile)

#endif
