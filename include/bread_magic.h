/**
 * @file bread_magic.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_magic_h
#define bread_magic_h

#include <stdlib.h>
#include "breads.h"

int bread_magic(ClassFile *class, FILE *classfile);

#endif
