#include "../include/bprint_classfile.h"

void bprint_classfile(ClassFile *class){
  bprint_magic(class);
  bprint_versions(class);
  bprint_const_pool_count(class);
  bprint_constant_pool(class);
  bprint_access_flags(class);
  bprint_this_class(class);
  bprint_super_class(class);
  bprint_interfaces_count(class);
  bprint_interfaces(class);
  bprint_fields_count(class);
  bprint_fields(class);
  bprint_methods_count(class);
  bprint_methods(class);
  bprint_attributes_count(class);
  bprint_attributes(class->attributes, class->attributes_count, "");
  return;
}

void bprint_info(cp_info *cp, const char *prefix){
  switch(cp->tag){
    case CONSTANT_Class:
      printf("%sName index: %d\n", prefix, cp->info->Class.name_index);
      break;
    case CONSTANT_Fieldref:
    case CONSTANT_Methodref:
    case CONSTANT_InterfaceMethodref:
      printf(
          "%sClass index: %d\n%sName and type index: %d\n",
          prefix, cp->info->Fieldref.class_index,
          prefix, cp->info->Fieldref.name_and_type_index
      );
      break;
    case CONSTANT_String:
      printf("%sString index: %d\n", prefix, cp->info->String.string_index);
      break;
    case CONSTANT_Integer:
    case CONSTANT_Float:
      printf("%sBytes: %d\n", prefix, cp->info->Integer.bytes);
      break;
    case CONSTANT_Long:
    case CONSTANT_Double:
      printf(
          "%sHigh bytes: 0x%08x\n%sLow bytes: 0x%08x\n",
          prefix, cp->info->Long.high_bytes,
          prefix, cp->info->Long.low_bytes
      );
      break;
    case CONSTANT_NameAndType:
      printf(
          "%sName index: %d\n%sDescripitor index: %d\n",
          prefix, cp->info->NameAndType.name_index,
          prefix, cp->info->NameAndType.descriptor_index
      );
      break;
    case CONSTANT_Utf8:
      printf("%sLength: %d\n%sBytes: \"", prefix, cp->info->Utf8.length, prefix);
      for(int i = 0; i < cp->info->Utf8.length; i++)
        printf("%c", cp->info->Utf8.bytes[i]);
      printf("\"\n");
      /*  printf("%02x ", cp->info->Utf8.bytes[i]);
      printf("\b\"\n");*/
      break;
  }
  return;
}
