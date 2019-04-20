#include "../include/bread_classfile.h"

ClassFile * bread_classfile(FILE *classfile){

  ClassFile *class = (ClassFile *) malloc(sizeof(ClassFile));

    /* Magic number */
  if(bread_magic(class, classfile)){
    free(class);
    fprintf(stderr, "Invalid .class file. Magic number \"0xcafebabe\" does not check.\n");
    exit(ERR_MAGIC);
  }
    /* Minor and major versions */
  bread_minor(class, classfile);
  bread_major(class, classfile);
    /* Constant pool count and constant pool */
  bread_constant_pool(class, classfile);
    /* Access flags, this class and super class */
  bread_access_flags(class, classfile);
  bread_this_class(class, classfile);
  bread_super_class(class, classfile);
    /* Interfaces count and interfaces */
  bread_interfaces(class, classfile);
    /* Fields count and fields */
  bread_fields(class, classfile);
    /* Methods */
  bread_methods(class, classfile);
    /* Attributes */
  bread_attributes_count(class, classfile);
  bread_attributes(class->attributes, class->attributes_count, classfile);

  return class;
}
