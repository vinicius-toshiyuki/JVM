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


void bprint_att_info(u1 *u1_stream, int name_index, ClassFile *class, const char prefix[]){
  static char attributes_types[ATT_C][ATT_M_S] = {"Code", "ConstantValue", "Deprecated", "Exceptions", "LineNumberTable", "LocalVariableTable", "SourceFile"};
  #ifndef att_type_value_assign
  #define att_type_value_assign
    // A enum NUMBERS tem que estar de acordo com essa numeração
    for(int i = 0; i < ATT_C; i++)
      attributes_types[i][ATT_M_S - 1] = i;
  #endif
  // Busca nome do atributo com o name_index na constant_pool
  
  char str_name[ATT_M_S];
  memcpy(str_name, class->constant_pool[name_index - 1].info->Utf8.bytes  /*Bytes do nome do atributo*/, class->constant_pool[name_index].info->Utf8.length);
  int number_code = ((char *) (bsearch(str_name, attributes_types, ATT_C, ATT_M_S, (int (*)(const void *, const void *)) strcmp)))[ATT_M_S - 1];
  printf(BGC(27) "%s%s attribute:" CLEARN, prefix, str_name);
  switch(number_code){ // Vou para o código correto para imprimir o atributo
    case NUMBER_Code:;
      Attributes att_info;
      u1_to_Code(att_info.Code, u1_stream);
      printf(
          "%s\tMax stack: %d\n"
          "%s\tMax locals: %d\n"
          "%s\tCode length: %d\n"
          "%s\tCode: \"",
          prefix, att_info.Code.max_stack,
          prefix, att_info.Code.max_locals,
          prefix, att_info.Code.code_length, prefix
      );
      for(int i = 0; i < att_info.Code.code_length; i++)
        printf("%02x ", att_info.Code.code[i]);
      printf("\b\"\n");
      break;
    case NUMBER_ConstantValue:
      break;
    case NUMBER_Deprecated:
      break;
    case NUMBER_Exceptions:
      break;
    case NUMBER_LineNumberTable:
      break;
    case NUMBER_LocalVariableTable:
      break;
    case NUMBER_SourceFile:
      break;
    default:
      break;
  }

  return;
}
