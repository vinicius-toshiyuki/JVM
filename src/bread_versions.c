#include <stdio.h>
#include <stdlib.h>
#include "../include/bread_versions.h"

void bread_minor(ClassFile *class, FILE *classfile){
  u2_read(class->minor_version, classfile);
  return;
}

void bread_major(ClassFile *class, FILE *classfile){
  u2_read(class->major_version, classfile);
  return;
}
