/**
 * @file bread_methods.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_methods_h
#define bread_methods_h

#include "breads.h"

void bread_methods(ClassFile *class, FILE *classfile);

#define bread_methods_count(__class, __classfile) u2_read(__class->methods_count, __classfile);

#endif
