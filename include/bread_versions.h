#ifndef bread_versions_h
#define bread_versions_h

#include <stdlib.h>
#include "breads.h"

int bread_minor(ClassFile *class, FILE *classfile);
int bread_major(ClassFile *class, FILE *classfile);

#endif
