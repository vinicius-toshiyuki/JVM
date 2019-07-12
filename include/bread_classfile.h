/**
 * @file bread_classfile.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to read the classfile.
 */
#ifndef bread_classfile_h
#define bread_classfile_h

#include "breads.h"

ClassFile * bread_classfile(FILE *classfile, char *filename);

#endif
