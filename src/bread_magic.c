#include <stdio.h>
#include <stdlib.h>
#include "../include/bread_magic.h"

int bread_magic(ClassFile *class, FILE *classfile){
	u4_read(class->magic, classfile);
	return class->magic == 0xcafebabe ? 0 : 1;
}
  
