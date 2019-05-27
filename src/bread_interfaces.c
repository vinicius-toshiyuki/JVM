#include <stdio.h>
#include <stdlib.h>
#include "../include/bread_interfaces.h"

void bread_interfaces(ClassFile *class, FILE *classfile){

  bread_interfaces_count(class, classfile);

  class->interfaces = (u2 *) malloc(sizeof(u2) * class->interfaces_count);

  for(int i = 0; i < class->interfaces_count; i++)
    u2_read(class->interfaces[i], classfile);

  return;
}
