#include "../include/bread_methods.h"
#include "../include/colors.h"

extern int verbose;

void bread_methods(ClassFile *class, FILE *classfile){

  bread_methods_count(class, classfile);

  class->methods = (method_info *) malloc(sizeof(method_info) * class->methods_count);

  for(int i = 0; i < class->methods_count; i++){
    u2_read(class->methods[i].access_flags, classfile);
    u2_read(class->methods[i].name_index, classfile);
    u2_read(class->methods[i].descriptor_index, classfile);
    u2_read(class->methods[i].attributes_count, classfile);

    class->methods[i].attributes = (attribute_info *) malloc(sizeof(attribute_info) * class->methods[i].attributes_count);

    for(int j = 0; j < class->methods[i].attributes_count; j++)
      bread_attributes(
          &(class->methods[i].attributes[j]),
          class->methods[i].attributes_count,
          classfile
      );
  }

  return;
}
