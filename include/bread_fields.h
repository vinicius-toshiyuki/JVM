/**
 * @file bread_fields.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_fields_h
#define bread_fields_h

#include <stdio.h>
#include "breads.h"

void bread_fields(ClassFile *class, FILE *classfile);

#define bread_fields_count(__class, __classfile) u2_read(__class->fields_count, __classfile)

#endif
