#ifndef bread_versions_h
#define bread_versions_h

#include "classfile.h"
#include "types.h"

void bread_minor(ClassFile *class, FILE *classfile);
void bread_major(ClassFile *class, FILE *classfile);

#endif
