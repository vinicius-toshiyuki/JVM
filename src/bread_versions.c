#include <stdio.h>
#include <stdlib.h>
#include "../include/bread_versions.h"

int bread_minor(ClassFile *class, FILE *classfile){
  u2_read(class->minor_version, classfile);
  return class->minor_version;
}

int bread_major(ClassFile *class, FILE *classfile){
  u2_read(class->major_version, classfile);
  return class->major_version;
}
