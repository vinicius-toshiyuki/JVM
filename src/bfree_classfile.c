#include "../include/bfree_classfile.h"

void bfree_classfile(ClassFile *class){
  for(int i = 0; i < class->const_pool_count - 1; i++){
    if(class->constant_pool[i].tag == CONSTANT_Utf8)
      free(class->constant_pool[i].info->Utf8.bytes);
    free(class->constant_pool[i].info);
  }

  free(class->constant_pool);

  free(class->interfaces);

  for(int i = 0; i < class->fields_count; i++)
    bfree_attributes(class->fields[i].attributes, class->fields[i].attributes_count);

  free(class->fields);

  for(int i = 0; i < class->methods_count; i++)
    bfree_attributes(class->methods[i].attributes, class->methods[i].attributes_count);

  free(class->methods);

  bfree_attributes(class->attributes, class->attributes_count);

  free(class);

  return;
}

void bfree_attributes(attribute_info *atts, int att_count){
  for(int i = 0; i < att_count; i++)
    free(atts[i].info);
  free(atts);
  return;
}
