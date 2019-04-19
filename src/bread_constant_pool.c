#include <stdio.h>
#include <stdlib.h>
#include "../include/bread_constant_pool.h"
#include "../include/errcodes.h"

/* Constant pool count */
int cpc;

void bread_constant_pool(ClassFile *class, FILE *classfile){
  bread_constant_pool_count(class, classfile);
  bread_constant_pool_info(class, classfile);
  return;
}

void bread_constant_pool_count(ClassFile *class, FILE *classfile){
  u2_read(class->const_pool_count, classfile);
  cpc = class->const_pool_count;
  return;
}

int bread_constant_pool_tag(cp_info *cp, FILE *classfile){
  u1_read(cp->tag, classfile);
  return cp->tag;
}

void bread_constant_pool_info(ClassFile *class, FILE *classfile){
  class->constant_pool = (cp_info *) malloc(sizeof(cp_info) * (cpc - 1));
  for(int i = 0; i < cpc - 1; i++){
    cp_info *cp = &(class->constant_pool[i]);
    cp->info = (info_t *) malloc(sizeof(info_t));
    switch(bread_constant_pool_tag(cp, classfile)){
      case CONSTANT_Class:
        bread_class_info(&(cp->info->Class), classfile); break;
      case CONSTANT_Fieldref:
        bread_fieldref_info(&(cp->info->Fieldref), classfile); break;
      case CONSTANT_Methodref:
        bread_methodref_info(&(cp->info->Methodref), classfile); break;
      case CONSTANT_InterfaceMethodref:
        bread_interfacemethodref_info(&(cp->info->InterfaceMethodref), classfile); break;
      case CONSTANT_String:
        bread_string_info(&(cp->info->String), classfile); break;
      case CONSTANT_Integer:
        bread_integer_info(&(cp->info->Integer), classfile); break;
      case CONSTANT_Float:
        bread_float_info(&(cp->info->Float), classfile); break;
      case CONSTANT_Long:
        bread_long_info(&(cp->info->Long), classfile); break;
      case CONSTANT_Double:
        bread_double_info(&(cp->info->Double), classfile); break;
      case CONSTANT_NameAndType:
        bread_nameandtype_info(&(cp->info->NameAndType), classfile); break;
      case CONSTANT_Utf8:
        bread_utf8_info(&(cp->info->Utf8), classfile); break;
      default:
        fprintf(stderr, "Unknown constant pool tag: %d\n", cp->tag);
        exit(ERR_UNKTAG);
        break;
    }
  }
  return;
}
