/**
 * @file bread_versions.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_versions_h
#define bread_versions_h

#include <stdlib.h>
#include "breads.h"

int bread_minor(ClassFile *class, FILE *classfile);
int bread_major(ClassFile *class, FILE *classfile);

#endif
