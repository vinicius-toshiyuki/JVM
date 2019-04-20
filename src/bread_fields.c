#include "../include/bread_fields.h"

void bread_fields(ClassFile *class, FILE *classfile){
  bread_fields_count(class, classfile);

  class->fields = (field_info *) malloc(sizeof(field_info) * class->fields_count);
  for(int i = 0; i < class->fields_count; i++){
    u2_read(class->fields[i].access_flags, classfile);
    u2_read(class->fields[i].name_index, classfile);
    u2_read(class->fields[i].descriptor_index, classfile);
    u2_read(class->fields[i].attributes_count, classfile);

    class->fields[i].attributes = (attribute_info *) malloc(sizeof(attribute_info) * class->fields[i].attributes_count);

    bread_attributes(class->fields[i].attributes, class->fields[i].attributes_count, classfile);
  }
}
