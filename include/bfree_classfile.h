/**
 * @file bfree_classfile.h
 * @author Henrique Mariano
 * @author Vinicius Toshiyuki
 * @date 11 Jul 2019
 * @brief File contain the methods to free the classfile.
 */
#ifndef bfree_classfile_h
#define bfree_classfile_h

#include <stdlib.h>
#include "breads.h"

void bfree_classfile(ClassFile *class);
void bfree_attributes(attribute_info *atts, int att_count);

#endif
